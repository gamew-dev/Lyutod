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

#include <cstdint>

namespace dpp {

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

class BotSessionState;
class ButtonSessionState;
class ServerSessionState;
class UserSessionState;

class BotHandler
{
    public:

    /// ctor
    BotHandler(BotSessionState& bot_state,
               ButtonSessionState& button_state,
               ServerSessionState& server_state,
               UserSessionState& user_state);
    /*
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
    */
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

    /*
    void handleLog(const std::string& line);
    void makeAIRequest(dpp::cluster& bot,
                       dpp::snowflake channelID,
                       std::shared_ptr<UserSessionStruct> user,
                       std::shared_ptr<ServerSessionStruct> server,
                       std::string postdata,
                       dpp::http_headers headers);
    */


};

#endif // BOTHANDLER_H
