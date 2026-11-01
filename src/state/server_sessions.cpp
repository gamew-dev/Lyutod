#include "server_sessions.h"

bool ServerSessionState::Has(u_int64_t guild_id) const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.find(guild_id) != data_.end();
}

ServerSessionStructData& ServerSessionState::Get(u_int64_t guild_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(guild_id);
    if (it == data_.end()) {
        auto session = std::make_shared<ServerSessionStructData>();
        session->guild_id = guild_id;
        session->last_activity = std::chrono::steady_clock::now();
        it = data_.emplace(guild_id, session).first;
    } else {
        it->second->last_activity = std::chrono::steady_clock::now();
    }
    return *it->second;
}

std::shared_ptr<ServerSessionStructData> ServerSessionState::GetPtr(u_int64_t guild_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = data_.find(guild_id);
    if (it == data_.end()) {
        auto session = std::make_shared<ServerSessionStructData>();
        session->guild_id = guild_id;
        session->last_activity = std::chrono::steady_clock::now();
        it = data_.emplace(guild_id, session).first;
    } else {
        it->second->last_activity = std::chrono::steady_clock::now();
    }
    return it->second;
}

void ServerSessionState::Remove(u_int64_t guild_id) {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.erase(guild_id);
}

void ServerSessionState::Cleanup(std::chrono::minutes max_idle) {
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

size_t ServerSessionState::Size() const {
    std::lock_guard<std::mutex> lock(mutex_);
    return data_.size();
}

void ServerSessionState::Clear() {
    std::lock_guard<std::mutex> lock(mutex_);
    data_.clear();
}
