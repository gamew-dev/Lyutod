#ifndef COMMON_H
#define COMMON_H

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



struct BotConfigStructData {
    std::string owner_id;
    std::string bot_token;
    std::string ai_token;
    std::string version;

    bool chat_enabled;
    bool ai_enabled;
    bool commands_enabled;
    bool autorole_enabled;
    bool cencus_enabled;


    bool valid = false;
};

struct ButtonSessionStructData {

    u_int64_t owner;

    std::string type;
    std::string state;
    int page = 0;

    std::chrono::steady_clock::time_point last_activity;

};

// Server session data wrapped on struct
struct ServerSessionStructData {
    std::vector<std::string> history;
    std::chrono::steady_clock::time_point last_activity;

    u_int64_t guild_id = 0;
    u_int64_t open_message_id = 0;
    u_int64_t last_channel = 0;

    int input_usage = 0;
    int output_usage = 0;
};

struct UserSessionStructData {
    std::string memory;
    std::chrono::steady_clock::time_point last_activity;
};

#endif // COMMON_H
