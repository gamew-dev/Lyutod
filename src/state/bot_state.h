#ifndef BOT_STATE_H
#define BOT_STATE_H

#include <chrono>


class bot_state
{
public:
    bot_state();

    bool is_shutting_down_ = false;
    std::time_t start_time_;
};

#endif // BOT_STATE_H

// why the hell did i write this bot using c++
// aaaaaarrghh
