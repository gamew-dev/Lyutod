#include "button_sessions.h"

bool ButtonSessionState::Has(const std::string& event_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.find(event_id) != data_.end();
}

bool ButtonSessionState::Has(u_int64_t message_id) const {
    return Has(std::to_string(message_id));
}

ButtonSessionStructData& ButtonSessionState::Get(const std::string& event_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(event_id);
    if (it == data_.end()) {
        ButtonSessionStructData session;
        session.last_activity = std::chrono::steady_clock::now();
        it = data_.emplace(event_id, session).first;
    } else {
        it->second.last_activity = std::chrono::steady_clock::now();
    }
    return it->second;
}

ButtonSessionStructData& ButtonSessionState::Get(u_int64_t message_id) {
    return Get(std::to_string(message_id));
}

void ButtonSessionState::Set(const std::string& event_id, const ButtonSessionStructData& session) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_[event_id] = session;
    data_[event_id].last_activity = std::chrono::steady_clock::now();
}

void ButtonSessionState::Set(u_int64_t message_id, const ButtonSessionStructData& session) {
    Set(std::to_string(message_id), session);
}

void ButtonSessionState::Remove(const std::string& event_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.erase(event_id);
}

void ButtonSessionState::Remove(u_int64_t message_id) {
    Remove(std::to_string(message_id));
}

void ButtonSessionState::Cleanup(std::chrono::minutes max_idle) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto now = std::chrono::steady_clock::now();
    for (auto it = data_.begin(); it != data_.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_activity);
        if (elapsed >= max_idle) {
            it = data_.erase(it);
        } else {
            ++it;
        }
    }
}

size_t ButtonSessionState::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.size();
}

void ButtonSessionState::Clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.clear();
}
