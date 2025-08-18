/**
 *  InputHandler.h
 *
 *  @brief Declaration of the InputHandler class
 *
 *  This class is designed to be the main controller for the program,
 *  in which it handles the inputs it receives and processes them for later use.
 *  The InputHandler class is responsible for creating messages, reacting
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

        // ctor
        BotHandler();

        // dtor
        //virtual ~BotHandler();



        void //preRegBot             (      dpp::cluster& bot)             , // todo: moved to config

             preRegSlash           (      dpp::cluster& bot)             , // for slash command declaration

             preDelSlash           (      dpp::cluster& bot)             ,

             handleSlash        (      dpp::cluster& bot,
                                 const dpp::slashcommand_t& event)    , // for handling slash command

             handleMessage      (      dpp::cluster& bot,
                                 const dpp::message_create_t& event)  , // for message type event

             handleGuildNewMem  (      dpp::cluster& bot,
                                 const dpp::guild_member_add_t& event), // when someone join server

             updatePresence     (      dpp::cluster& bot);


    private:

        std::time_t start                               ; // get bot start time

        std::vector <dpp::presence> presence {

            dpp::presence(dpp::ps_idle , dpp::at_watching  , "you..."),
            dpp::presence(dpp::ps_idle , dpp::at_competing , "lomba turu"),
            dpp::presence(dpp::ps_idle , dpp::at_listening , "your scream"),
            dpp::presence(dpp::ps_idle , dpp::at_streaming , "onlyAirConditioner")

        };

};

#endif // BOTHANDLER_H
