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

#include "config.h"
#include "utils.h"
#include "../services/responses_chat.h"
#include "../command/base_commands.h"
#include "../command/base_commands_ui.h"

namespace dpp {

using snowflake = uint64_t; //final type

struct cluster;
struct ready_t;
struct log_t;
struct message_create_t;
struct slashcommand_t;
struct button_click_t;
struct guild_member_add_t;
struct guild_member_remove_t;
struct guild_create_t;

}



class BotHandler
{
    public:

    /// ctor
    BotHandler(BotSessionState& bot_state,
               ButtonSessionState& button_state,
               ServerSessionState& server_state,
               UserSessionState& user_state);

    void preRegSlash        (      dpp::cluster& bot,
                                    dpp::snowflake id)             , /// Slash command Register

         preDelSlash        (      dpp::cluster& bot,
                                    dpp::snowflake id)             , /// Slash command Deletion

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

    // =====================================================================================
    // REFACTOR NEW LOGIC START HERE

    void OnReady(dpp::cluster& bot, const dpp::ready_t& event);
    void OnLog(dpp::cluster& bot, const dpp::log_t& event);
    void OnMessageCreate(dpp::cluster& bot, const dpp::message_create_t& event);
    void OnSlashCommand(dpp::cluster& bot, const dpp::slashcommand_t& event);
    void OnButtonClick(dpp::cluster& bot, const dpp::button_click_t& event);
    void OnGuildMemberAdd(dpp::cluster& bot, const dpp::guild_member_add_t& event);
    void OnGuildMemberRemove(dpp::cluster& bot, const dpp::guild_member_remove_t& event);
    void OnGuildCreate(dpp::cluster& bot, const dpp::guild_create_t& event);
    void OnTimer();




    private:

    BotSessionState& bot_state;
    ButtonSessionState& button_state;
    ServerSessionState& server_state;
    UserSessionState& user_state;


    /// ---------------------------

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

        dpp::snowflake guildID = 0;
        dpp::snowflake openMessageID = 0;
        dpp::snowflake lastChannel = 0;

        int inputUsage = 0;
        int outputUsage = 0;
    };

    struct MessageSessionStruct {

        dpp::snowflake owner;

        std::string type;
        std::string state;
        int page = 0;

        std::chrono::steady_clock::time_point last_activity;

    };


    void handleLog(const std::string& line);
    void makeAIRequest(dpp::cluster& bot,
                       dpp::snowflake channelID,
                       std::shared_ptr<UserSessionStruct> user,
                       std::shared_ptr<ServerSessionStruct> server,
                       std::string postdata,
                       dpp::http_headers headers);



    /// The map for session pairin',
    //  the first index will be using user and/or server's id. for example, user has an id of 123456789
    //  therefore it will be UserSessions[123...9] = UserSessionStruct{"i like trains", 69 years ago}
    //  same happen with the server session, good thing about u_map is there are no ordered index 1,2,3 like an array for looping
    //  instead, it will check if it has value or not.
    ///  @Todo:
    std::unordered_map<dpp::snowflake, std::shared_ptr<UserSessionStruct>> UserSessions;
    std::unordered_map<dpp::snowflake, std::shared_ptr<ServerSessionStruct>> ServerSessions;

    /// Map for active message
    //  An active message that has an interface/interactive feature such as menu selection, button
    //  edit, modal, etc
    //  WIP...
    std::unordered_map<dpp::snowflake, MessageSessionStruct> MessageSession;

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
