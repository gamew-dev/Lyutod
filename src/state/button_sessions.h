#ifndef BUTTON_SESSIONS_H
#define BUTTON_SESSIONS_H

#include <string>
#include <chrono>

namespace dpp {
    using snowflake = u_int64_t;
}

struct ButtonSession {

    dpp::snowflake owner;

    std::string type;
    std::string state;
    int page = 0;

    std::chrono::steady_clock::time_point last_activity;

};

class ButtonSessionState {
public:
    button_sessions();
    ButtonSession& Get(const std::string& event_id);

};

#endif // BUTTON_SESSIONS_H
