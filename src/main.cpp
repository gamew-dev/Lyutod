/**
 * Lyudya
 *
 * Discord multipurpose bot
 * A bot written to have some fun and spice up chat
 *
 * @author Hissats
 */


#include "core/bothandler/BotHandler.h"

int main() {

    // Local variabel to save the token
    // I know it's bad conduct but whatever, later i fix it lol
    // TODO: maybe throw exception
    std::string token;

    // Load bot config, the function return true if the config valid
    if (Config::clientLoadConfig()) {
        token = Config::botToken;
    }
    else {
        std::cout << "no token files found" << std::endl;
        return 1;
    }

    // Initialize the bot object
    dpp::cluster bot(token, dpp::i_all_intents);
    // Initialize custom class Bothandler object
    // the BotHandler class is a event handler designed to process the input
    // given by the event, more on it in the file @BotHandler.h/cpp
    BotHandler handler;


    // From now on, you are gonna see most bot event logic "bot.on_something".
    // Each function is called an event listener and works asynchronously.
    // Every supported event is handled here and passed to the BotHandler class.

    // D++ built in log system, though in this function i only filtered the [Info] only
    bot.on_log([](const dpp::log_t& event) {
        if (event.severity == dpp::ll_info) {
                std::cout << "[INFO] " << event.message << std::endl;
            }
    });


    // When the bot started active
    bot.on_ready([&bot, &handler](const dpp::ready_t& event) {

        std::cout << "\e[0;33m"<<"[INFO]" << "\e[0m" << " Starting bot..." << std::endl;

        // Registering slash command
        // keep in mind as far as now, this code is still testing
        // and some of the code is still hardcoded including this one

        //1349036976627777557
        //1270735247922692177

        //handler.preRegSlash(bot, 1270735247922692177);
        ///handler.preDelSlash(bot, 1349036976627777557);

        // First time startup resence setting
        bot.set_presence(dpp::presence(dpp::ps_online  , dpp::at_custom   , "hello world"));

        // Bot timer, for every 10 minutes bot is changing presence status
        // and checking chatbot sessions
        bot.start_timer([&bot, &handler](const dpp::timer& timer){

            handler.updatePresence(bot);
            Config::cooldownBsok = false;

            if (!Config::isShutingDown) {
                handler.checkSessions(bot, false);
            }


        },600);

    }); //on-ready



    // When a message is created in any channel the bot can see, it will run this code
    bot.on_message_create([&bot, &handler](const dpp::message_create_t& event) {

        // Avoid bot self reply
        if (event.msg.author.id == bot.me.id) return;


        std::cout << event.msg.author.global_name << ": " << event.msg.content << std::endl;

        // Throw the event for InputHandler to manage
        // for every message that mentions the bot, it
        // will be treat as chatbot for ai
        if (Utils::isMentioned(bot, event)) {
            std::cout << "bot Mentioned" << std::endl;

            handler.handleAiRequest(bot, event);
        } else {

            handler.handleMessage(bot, event);
        }


    }); // chat



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
            std::cout << "[INFO] Checking guild cache" <<std::endl;
        }

        // Call the guild create config function and return true if succes
        // send a greeting/join chat in server system channel
        if (Config::guildCreateConfig(event)) {
            std::string repl = Responses::makeMsg("invite", bot.me, false);
            bot.message_create(dpp::message(event.created.system_channel_id, repl));
            //std::cout << "" << std::endl;
        }

    });

    // Start the bot
    bot.start(dpp::st_wait);
}


