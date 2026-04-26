#ifndef BUTTON_SESSIONS_H
#define BUTTON_SESSIONS_H

#include "shared/data.h"

class ButtonSessionState {
public:
    button_sessions();
    ButtonSession& Get(const std::string& event_id);

};

#endif // BUTTON_SESSIONS_H
