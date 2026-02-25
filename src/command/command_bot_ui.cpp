#include "command/base_commands_ui.h"
#include "../core/bothandler/BotHandler.h" //lmao later i fix


namespace button_commands {
void bot_ui(dpp::cluster& bot, const dpp::button_click_t& event, int& page) {


    if (event.custom_id == "cmd_status|right") {

        if (page != 1) {
            page = 1;
            bot.message_create(dpp::message(event.command.channel_id, "ok next"));
        }

    }
    else if (event.custom_id == "cmd_status|left") {

        if (page != 0) {
            page = 0;
            bot.message_create(dpp::message(event.command.channel_id, "ok prev"));
        }
    }
}
}
