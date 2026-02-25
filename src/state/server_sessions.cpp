#include "state/server_sessions.h".h"
/*
ServerSession& ServerSessionStore::Get(dpp::snowflake guild_id) {
    auto it = data_.find(guild_id);
    if (it == data_.end()) {
        it = data_.emplace(guild_id, std::make_unique<ServerSession>()).first;
    }
    it->second->last_activity = std::chrono::steady_clock::now();
    return *it->second;
}
*/
