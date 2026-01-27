#ifndef SERVER_SESSIONS_H
#define SERVER_SESSIONS_H

/// A struct to pair with ServerSession map for chatbotSession
//  keeps the chat history, last chat, last chat channel id
//  and token usage
struct ServerSessionStruct {
    std::vector<std::string> history;
    std::chrono::steady_clock::time_point last_activity;

    dpp::snowflake guildID = 0;
    dpp::snowflake openMessageID = 0;
    dpp::snowflake lastChannel = 0;

    int inputUsage = 0;
    int outputUsage = 0;
};


#endif // SERVER_SESSIONS_H
