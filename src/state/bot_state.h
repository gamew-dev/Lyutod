#ifndef BOT_STATE_H
#define BOT_STATE_H

#include "shared/data.h"

#include <chrono> // time_t
#include <string> // string



class BotSessionState
{
public:
    BotSessionState(const BotConfig& config);

    bool is_shutting_down_ = false;
    bool is_logging = true;

    std::time_t start_time_;

    const std::string& GetBotToken() const;
    const std::string& GetGPTToken() const;
    const std::string& GetOwnerID() const;

    const PresenceData& GetPresence() const;

private:
    std::vector <PresenceData> presence;

    std::string bot_token_;
    std::string gpt_token_;
    std::string owner_id_;


};

#endif // BOT_STATE_H

// why the hell did i write this bot using c++
// aaaaaarrghh
