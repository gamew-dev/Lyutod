#include "user_sessions.h"

u_int64_t UserSessionState::ParseUserId(const std::string& id_str) {
    if (id_str.empty()) return 0;
    try {
        return std::stoull(id_str);
    } catch (...) {
        return 0;
    }
}

bool UserSessionState::Has(u_int64_t user_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.find(user_id) != data_.end();
}

bool UserSessionState::Has(const std::string& user_id) const {
    return Has(ParseUserId(user_id));
}

UserSessionStructData& UserSessionState::Get(u_int64_t user_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(user_id);
    if (it == data_.end()) {
        auto session = std::make_shared<UserSessionStructData>();
        session->last_activity = std::chrono::steady_clock::now();
        it = data_.emplace(user_id, session).first;
    } else {
        it->second->last_activity = std::chrono::steady_clock::now();
    }
    return *it->second;
}

UserSessionStructData& UserSessionState::Get(const std::string& user_id) {
    return Get(ParseUserId(user_id));
}

std::shared_ptr<UserSessionStructData> UserSessionState::GetPtr(u_int64_t user_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(user_id);
    if (it == data_.end()) {
        auto session = std::make_shared<UserSessionStructData>();
        session->last_activity = std::chrono::steady_clock::now();
        it = data_.emplace(user_id, session).first;
    } else {
        it->second->last_activity = std::chrono::steady_clock::now();
    }
    return it->second;
}

std::shared_ptr<UserSessionStructData> UserSessionState::GetPtr(const std::string& user_id) {
    return GetPtr(ParseUserId(user_id));
}

void UserSessionState::Remove(u_int64_t user_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.erase(user_id);
}

void UserSessionState::Remove(const std::string& user_id) {
    Remove(ParseUserId(user_id));
}

void UserSessionState::Cleanup(std::chrono::minutes max_idle) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto now = std::chrono::steady_clock::now();
    for (auto it = data_.begin(); it != data_.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second->last_activity);
        if (elapsed >= max_idle) {
            it = data_.erase(it);
        } else {
            ++it;
        }
    }
}

size_t UserSessionState::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.size();
}

void UserSessionState::Clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.clear();
}
