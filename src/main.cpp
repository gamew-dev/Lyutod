
/**
 * Bapenikov
 *
 * Discord random reply chat bot
 * A bot written to have some fun and spice up chat
 *
 * @author Hissats
 */


#include "BotHandler.h"
//#include "Terminal.h"


int main() {

    std::string token;

    if (Config::clientLoadConfig()) {
        token = Config::botToken;
    }

    // terminate the program if token unavailable or invalid
    else {
        std::cout << "no token" << std::endl;
        return 1;
    }

    //bot.on_log(dpp::utility::cout_logger());
    dpp::cluster bot(token, dpp::i_all_intents);

    bot.on_log([](const dpp::log_t& event) {
        if (event.severity == dpp::ll_info) {
                std::cout << "[INFO] " << event.message << std::endl;
            }
    });


    // initialize the object of InputHandler class and
    // register the bot config, identity, and slash

    BotHandler handler;

    // when the bot successfully connects to Discord,
    // it will initialize the slash command declaration once and,
    // set the bot presence status
    bot.on_ready([&bot, &handler](const dpp::ready_t& event) {

        std::cout << "\e[0;33m"<<"[INFO]" << "\e[0m" << " Starting bot..." << std::endl;

        handler.preRegSlash(bot);

        // presence setting and output message when online
        bot.set_presence(dpp::presence(dpp::ps_online  , dpp::at_custom   , "hello world"));

        bot.start_timer([&bot, &handler](const dpp::timer& timer){

            handler.updatePresence(bot);
            if (!Config::isShutingDown) {
                handler.checkSessions(bot, false);
            }


        },300);

    }); //on-ready



    // When a message is created in any channel the bot can see, it will run this code
    bot.on_message_create([&bot, &handler](const dpp::message_create_t& event) {

        // Avoid bot self reply
        if (event.msg.author.id == bot.me.id) return;

        // A simple logger for checking messagge content and who sends it
        std::cout << event.msg.author.global_name << ": " << event.msg.content << std::endl;

        // Throw the event for InputHandler to manage

        if (Utils::isMentioned(bot, event)) {
            std::cout << "bot Mentioned" << std::endl;
            handler.handleAiRequest(bot, event);
        } else {
            handler.handleMessage(bot, event);
        }


    }); // baca-bales chat



    // When the slash command is triggered this will run

    bot.on_slashcommand([&bot, &handler](const dpp::slashcommand_t& event) {

        handler.handleSlash(bot, event);
    }); //slash command


    bot.on_button_click([&bot, &handler] (const dpp::button_click_t& event) {

        handler.handleButtonEvent(bot, event);
    });

    // When a new member shows up

    bot.on_guild_member_add([&bot, &handler](const dpp::guild_member_add_t& event) {

        handler.handleGuildNewMem(bot, event);
    });


    bot.on_guild_create([&bot](const dpp::guild_create_t& event) {


        if (dpp::run_once<struct logging>()) {
            std::cout << "[INFO] Checking guild cache" <<std::endl;
        }

        if (Config::guildCreateConfig(event)) {
            std::string repl = Responses::makeMsg("invite", bot.me, false);
            bot.message_create(dpp::message(event.created.system_channel_id, repl));
        }

    });


    // Start the bot
    bot.start(dpp::st_wait);
}


