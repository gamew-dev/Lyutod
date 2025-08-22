
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

    // find and open the token file
    // token get stored in string variable
    std::ifstream getToken("data/client/token.txt");
    std::string token;

    if (getToken) {
        getToken >> token;
        getToken.close();
    }

    // terminate the program if token unavailable or invalid
    else {
        std::cout << "no token" << std::endl;
        return 1;
    }

    // initialize bot object and its intents
    dpp::cluster bot(token, dpp::i_all_intents);

    //bot.on_log(dpp::utility::cout_logger());
    bot.on_log([](const dpp::log_t& event) {
        if (event.severity == dpp::ll_info) {
                std::cout << "[INFO] " << event.message << std::endl;
            }
    });


    // initialize the object of InputHandler class and
    // register the bot config, identity, and slash
    /** old
    InputHandler handler;
    handler.regBot(bot);
    */
    BotHandler handler;

    // when the bot successfully connects to Discord,
    // it will initialize the slash command declaration once and,
    // set the bot presence status
    bot.on_ready([&bot, &handler](const dpp::ready_t& event) {

        if (dpp::run_once<struct register_bot_commands>()) {

            std::cout << "\e[0;33m"<<"[INFO]" << "\e[0m" << " Starting bot..." << std::endl;
        }

        // presence setting and output message when online
        bot.set_presence(dpp::presence(dpp::ps_online  , dpp::at_custom   , "hello world"));

        bot.start_timer([&bot, &handler](const dpp::timer& timer){

            handler.updatePresence(bot);


        },300);

    }); //on-ready



    // When a message is created in any channel the bot can see, it will run this code
    bot.on_message_create([&bot, &handler](const dpp::message_create_t& event) {

        // Avoid bot self reply
        if (event.msg.author.id == bot.me.id) return;

        // A simple logger for checking messagge content and who sends it
        std::cout << event.msg.author.global_name << ": " << event.msg.content << std::endl;

        // Throw the event for InputHandler to manage
        handler.handleMessage(bot, event);


    }); // baca-bales chat



    // When the slash command is triggered this will run

    bot.on_slashcommand([&bot, &handler](const dpp::slashcommand_t& event) {

        handler.handleSlash(bot, event);
    }); //slash command



    // When a new member shows up

    bot.on_guild_member_add([&bot, &handler](const dpp::guild_member_add_t& event) {

        handler.handleGuildNewMem(bot, event);
    });


    bot.on_guild_create([&bot](const dpp::guild_create_t& event) {


        Config::guildCreateConfig(event);

    });


    // Start the bot
    bot.start(dpp::st_wait);
}


