#ifndef BOT_STATE_H
#define BOT_STATE_H

#include <chrono>


class BotSessionState
{
public:
    BotSessionState();

    bool is_shutting_down_ = false;
    bool is_logging = true;

    std::time_t start_time_;
};

#endif // BOT_STATE_H

// why the hell did i write this bot using c++
// aaaaaarrghh
