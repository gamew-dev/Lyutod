/**
 *  BotHandler.h
 *
 *  @brief Declaration of the BotHandler class
 *
 *  This class is designed to be the main controller for the program/bot flow,
 *  in which it handles the inputs it receives and processes them for later use.
 *  The BotHandler class is responsible for creating messages, reacting
 *  to messages, and handling various commands.
 *
 *  @author Hissats
 */

#ifndef BOTHANDLER_H
#define BOTHANDLER_H

#include "Config.h"
#include "Utils.h"
#include "Responses.h"
#include "../../command/base_commands.h"

class BotHandler
{
    public:

    /// ctor
    BotHandler();


    void preRegSlash        (      dpp::cluster& bot)             , /// Slash command Register

         preDelSlash        (      dpp::cluster& bot)             , /// Slash command Deletion

         handleSlash        (      dpp::cluster& bot,               /// Handling slash command
                                 const dpp::slashcommand_t& event    ) ,

         handleMessage      (      dpp::cluster& bot,               /// Message type event
                                 const dpp::message_create_t& event  ) ,

         handleAiRequest    (      dpp::cluster& bot,               /// Manage chatbot event
                                 const dpp::message_create_t& event  ) ,

         handleGuildNewMem  (      dpp::cluster& bot,               /// When someone join server
                                 const dpp::guild_member_add_t& event) ,

         handleGuildRemMem  (      dpp::cluster& bot,               /// When someone leave server
                                 const dpp::guild_member_remove_t& event),

         handleButtonEvent  (      dpp::cluster& bot,               /// Button pressed
                                 const dpp::button_click_t& event    ) ,

         updatePresence     (      dpp::cluster& bot             ) ,/// Presence

         checkSessions      (      dpp::cluster& bot,               /// Chatbot session and memory
                                 const bool& forced                  );


    private:

    /// get bot time when the startup at
    //  the value will be init in ctr
    //  and used it some command ex: status
    std::time_t start;


    /// A struct to pair with UserSession map for chatbotSession
    //  hold the user memory and last time chat value
    struct UserSessionStruct {
        std::string memory;
        std::chrono::steady_clock::time_point last_activity;
    };

    /// A struct to pair with ServerSession map for chatbotSession
    //  keeps the chat history, last chat, last chat channel id
    //  and token usage
    struct ServerSessionStruct {
        std::vector<std::string> history;
        std::chrono::steady_clock::time_point last_activity;
        dpp::snowflake lastChannel;
        int inputUsage = 0;
        int outputUsage = 0;
    };

    /// The map for session pairin,
    //  the first index will be using user and/or server's id. for example, user has an id of 123456789
    //  therefore it will be UserSessions[123...9] = UserSessionStruct{"i like trains", 69 years ago}
    //  same happen with the server session, good thing about u_map is there are no ordered index 1,2,3 like an array for looping
    //  instead, it will check if it has value or not.
    ///  @Todo:
    std::unordered_map<dpp::snowflake, UserSessionStruct> UserSessions;
    std::unordered_map<dpp::snowflake, ServerSessionStruct> ServerSessions;

    /// Presence list that available for the bot
    std::vector <dpp::presence> presence {

        dpp::presence(dpp::ps_idle , dpp::at_watching  , "you..."),
        dpp::presence(dpp::ps_idle , dpp::at_competing , "lomba turu"),
        dpp::presence(dpp::ps_idle , dpp::at_listening , "your scream"),
        dpp::presence(dpp::ps_idle , dpp::at_streaming , "onlyAirConditioner"),

        dpp::presence(dpp::ps_idle , dpp::at_watching  , "the world is ending"),
        dpp::presence(dpp::ps_idle , dpp::at_competing , "gooning tournament"),
        dpp::presence(dpp::ps_idle , dpp::at_listening , "burning pc"),
        dpp::presence(dpp::ps_idle , dpp::at_streaming , "a")

    };



};

#endif // BOTHANDLER_H
