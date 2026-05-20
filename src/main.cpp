/**
 * Lyudya
 *
 * Discord multipurpose bot
 * A bot written to have some fun and spice up chat
 *
 * @author Hissats
 */


#include "core/bot_handler.h"
#include "core/config.h"

#include "shared/data.h"

#include "state/bot_state.h"
#include "state/button_sessions.h"
#include "state/server_sessions.h"
#include "state/user_sessions.h"

int main() {

    ///-----

    BotConfig cfg = config::LoadBotConfig();

    if (!cfg.valid) return 1;

    dpp::cluster bot(cfg.bot_token, dpp::i_all_intents);

    //-------

    BotSessionState bot_state(cfg);
    ButtonSessionState button_state;
    ServerSessionState server_state;
    UserSessionState user_state;

    BotHandler handler(bot_state, button_state, server_state, user_state);


    // From now on, you are gonna see most bot event logic "bot.on_something".
    // Each function is called an event listener and works asynchronously.
    // Every supported event is handled here and passed to the BotHandler class.

    // D++ built in log system, though in this function i only filtered the [Info] only
    bot.on_log([](const dpp::log_t& event) {
        if (event.severity == dpp::ll_info) {
                if (Config::isLog) std::cout << "[INFO] " << event.message << std::endl;
            }
    });


    // When the bot started active
    bot.on_ready([&bot, &handler](const dpp::ready_t& event) {

        handler.OnReady(bot, event);

    }); //on-ready



    // When a message is created in any channel the bot can see, it will run this code
    bot.on_message_create([&bot, &handler](const dpp::message_create_t& event) {

        // Avoid bot self reply
        if (event.msg.author.id == bot.me.id) return;
        handler.OnMessageCreate(bot, event);

    }); // chat


    /*
    // When the slash command is triggered this will run

    bot.on_slashcommand([&bot, &handler](const dpp::slashcommand_t& event) {

        handler.handleSlash(bot, event);
    }); //slash command


    // Button clicked...
    bot.on_button_click([&bot, &handler] (const dpp::button_click_t& event) {

        handler.handleButtonEvent(bot, event);
    });


    // When a new member shows up
    bot.on_guild_member_add([&bot, &handler](const dpp::guild_member_add_t& event) {

        handler.handleGuildNewMem(bot, event);
    });

    // When a member leave guild
    bot.on_guild_member_remove([&bot, &handler](const dpp::guild_member_remove_t& event) {
        handler.handleGuildRemMem(bot, event);
    });

    // This logic is a bit annoying tbh, this one called for
    // every bot startup and when joined new server/guild.
    // Since this bot use multi config for each guild (see Config.h/cpp)
    // and we dont want it to be rewriten every bot startup, we can
    // use the built in dpp::run_once<>
    bot.on_guild_create([&bot](const dpp::guild_create_t& event) {


        // yet again, for now this code only hardcoded for my log status
        // see issues and to do for further info
        if (dpp::run_once<struct logging>()) {
            if (Config::isLog) std::cout << "[INFO] Checking guild cache" <<std::endl;
        }

        // Call the guild create config function and return true if succes
        // send a greeting/join chat in server system channel
        if (Config::guildCreateConfig(event)) {
            std::string repl = Responses::makeMsg("invite", bot.me, false);
            bot.message_create(dpp::message(event.created.system_channel_id, repl));
            //std::cout << "" << std::endl;
        }

    });
    */
    // Start the bot
    bot.start(dpp::st_wait);
}


