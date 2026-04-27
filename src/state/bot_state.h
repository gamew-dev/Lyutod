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

private:
    // move into shared/state.h later
    // or enum class
    std::vector <dpp::presence> presence {

        dpp::presence(dpp::ps_idle , dpp::at_watching  , "you..."),
        dpp::presence(dpp::ps_idle , dpp::at_competing , "lomba turu"),
        dpp::presence(dpp::ps_idle , dpp::at_listening , "your scream"),
        dpp::presence(dpp::ps_idle , dpp::at_streaming , "onlyAirConditioner"),

        dpp::presence(dpp::ps_idle , dpp::at_watching  , "the world is ending"),
        dpp::presence(dpp::ps_idle , dpp::at_competing , "gooning tournament"),
        dpp::presence(dpp::ps_idle , dpp::at_listening , "burning pc"),
        dpp::presence(dpp::ps_idle , dpp::at_streaming , "a")

    };

    std::string bot_token_;
    std::string gpt_token_;
    std::string owner_id_;


};

#endif // BOT_STATE_H

// why the hell did i write this bot using c++
// aaaaaarrghh
