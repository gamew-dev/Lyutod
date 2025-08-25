#ifndef COMMANDS_H
#define COMMANDS_H

#include "dpp/dpp.h"
#include "Responses.h"
#include "Utils.h"

class Commands {

    public:
    static void command_status(      const std::time_t& start,
                                           dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_server_info (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_say         (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_set_autorole(const dpp::slashcommand_t& event);

    static inline std::map<std::string, dpp::slashcommand> commands_list {
            {"1", dpp::slashcommand("status", "Info bot", 0)},

            {"2", dpp::slashcommand("server_info", "Cek status server", 0)},

            {"3", dpp::slashcommand("say", "Bot says icixiwir echo", 0)
                  .add_option(dpp::command_option(dpp::co_string, "pesan", "textny..", true))
                  .add_option(dpp::command_option(dpp::co_channel, "channel", "Channel tujuan", true))
            },

            {"4", dpp::slashcommand("set_autorole", "setting autorole server", 0)
                  .add_option(dpp::command_option(dpp::co_boolean, "set", "true/false", true))
                  .add_option(dpp::command_option(dpp::co_role, "role", "pilih role", false))
            },

            {"5", dpp::slashcommand("user_info", "lihat profil user", 0)
                  .add_option(dpp::command_option(dpp::co_user, "user", "pilih satu", true))
            }

        };
};


#endif // COMMANDS_H
