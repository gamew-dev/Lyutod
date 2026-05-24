#ifndef DATA_H
#define DATA_H

#include <string> // string
#include <chrono> // time_t
#include <vector> //vector

#include <cstdint>

//-----------------------------------------------------

enum class PresenceStatus {
    Idle,
    Online,
    Dnd
};

enum class ActivityType {
    Watching,
    Playing,
    Listening,
    Streaming,
    Competing
};

struct PresenceData {
    PresenceStatus status;
    ActivityType type;
    std::string text;
};

//----------------------------------------------------

struct BotConfig {
    std::string bot_token;
    std::string gpt_token;
    std::string owner_id;
    bool valid = false;
};

struct ButtonSession {

    u_int64_t owner;

    std::string type;
    std::string state;
    int page = 0;

    std::chrono::steady_clock::time_point last_activity;

};

// Server session data wrapped on struct
struct ServerSession {
    std::vector<std::string> history;
    std::chrono::steady_clock::time_point last_activity;

    u_int64_t guild_id = 0;
    u_int64_t open_message_id = 0;
    u_int64_t last_channel = 0;

    int input_usage = 0;
    int output_usage = 0;
};

struct UserSession {
    std::string memory;
    std::chrono::steady_clock::time_point last_activity;
};

#endif // DATA_H
