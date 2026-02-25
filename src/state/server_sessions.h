#ifndef SERVER_SESSIONS_H
#define SERVER_SESSIONS_H

/// A struct to pair with ServerSession map for chatbotSession
//  keeps the chat history, last chat, last chat channel id
//  and token usage

#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

// dpp placeholder
namespace dpp {
using snowflake = u_int64_t;
}

// Server session data wrapped on struct
struct ServerSession {
    std::vector<std::string> history;
    std::chrono::steady_clock::time_point last_activity;

    dpp::snowflake guild_id = 0;
    dpp::snowflake open_message_id = 0;
    dpp::snowflake last_channel = 0;

    int input_usage = 0;
    int output_usage = 0;
};

// Server session object wrapped as class
class ServerSessionStore {
    public:
    ServerSession& Get(dpp::snowflake guild_id);
    void Remove(dpp::snowflake guild_id);
    void Cleanup();

    template<typename Fn>
    void ForEach(Fn fn);

    private:
    std::unordered_map<dpp::snowflake, std::shared_ptr<ServerSession>> data_; //unique_ptr
    //std::unordered_map<dpp::snowflake, std::shared_ptr<ServerSession>> ServerSessions;
};


#endif // SERVER_SESSIONS_H
