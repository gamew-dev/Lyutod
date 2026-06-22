#ifndef BUTTON_SESSIONS_H
#define BUTTON_SESSIONS_H

#include "shared/common.h"

class ButtonSessionState {
public:
    ButtonSessionState();
    ButtonSessionStructData& Get(const std::string& event_id);

};

#endif // BUTTON_SESSIONS_H
