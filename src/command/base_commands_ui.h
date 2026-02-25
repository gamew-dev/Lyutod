#ifndef BASE_COMMANDS_UI_H
#define BASE_COMMANDS_UI_H

#include "dpp/dpp.h"
#include "../core/config/Config.h"
#include "../responses/Responses.h"
#include "../core/utils/Utils.h"

namespace button_commands {
void bot_ui(dpp::cluster& bot, const dpp::button_click_t& event, int& page);
}


#endif // BASE_COMMANDS_UI_H
