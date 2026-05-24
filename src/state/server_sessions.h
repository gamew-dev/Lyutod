#ifndef SERVER_SESSIONS_H
#define SERVER_SESSIONS_H

/// A struct to pair with ServerSession map for chatbotSession
//  keeps the chat history, last chat, last chat channel id
//  and token usage

#include "shared/data.h"

#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>


// Server session object wrapped as class
class ServerSessionState {
    public:
    ServerSession& Get(u_int64_t guild_id);
    void Remove(u_int64_t guild_id);
    void Cleanup();

    template<typename Fn>
    void ForEach(Fn fn);

    private:
    std::unordered_map<u_int64_t, std::shared_ptr<ServerSession>> data_; //unique_ptr
    //std::unordered_map<dpp::snowflake, std::shared_ptr<ServerSession>> ServerSessions;
};


#endif // SERVER_SESSIONS_H
