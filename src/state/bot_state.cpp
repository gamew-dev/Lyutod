#include "bot_state.h"

BotSessionState::BotSessionState(const BotConfig& config)
{
    bot_token_ = config.bot_token;
    gpt_token_ = config.gpt_token;
    owner_id_; = config.owner_id;
    start_time_ = std::time(nullptr);

    presence = {
        {PresenceStatus::Idle, ActivityType::Watching , "you..."},
        {PresenceStatus::Idle, ActivityType::Competing, "lomba turu"},
        {PresenceStatus::Idle, ActivityType::Listening, "your scream"},
        {PresenceStatus::Idle, ActivityType::Streaming, "onlyAirConditioner"},

        {PresenceStatus::Idle, ActivityType::Watching , "the world is ending"},
        {PresenceStatus::Idle, ActivityType::Competing, "gooning tournament"},
        {PresenceStatus::Idle, ActivityType::Listening, "burning pc"},
        {PresenceStatus::Idle, ActivityType::Streaming, "a"}
    };

}

const std::string& BotSessionState::GetBotToken() const {
    return bot_token_;
}

const std::string& BotSessionState::GetGPTToken() const {
    return gpt_token_;
}

const std::string& BotSessionState::GetOwnerID() const {
    return owner_id_;
}
