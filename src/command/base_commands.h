#ifndef COMMANDS_H
#define COMMANDS_H

#include "dpp/dpp.h"
#include "Config.h"
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
                command_set_autorole(      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_user_info   (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_member_count(      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_sync_guild  (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event);

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
                .set_default_permissions(dpp::p_administrator)
            },

            {"5", dpp::slashcommand("user_info", "lihat profil user", 0)
                .add_option(dpp::command_option(dpp::co_user, "user", "pilih satu", false))
            },
            // census
            {"6", dpp::slashcommand("set_member_count", "setting channel jumlah member", 0)
                .add_option(
                    dpp::command_option(dpp::co_sub_command, "add", "aktifkan member count")
                        .add_option(
                            dpp::command_option(dpp::co_string, "mode", "jenis member yang dihitung", true)
                                .add_choice(dpp::command_option_choice("semua members", "members"))
                                .add_choice(dpp::command_option_choice("human ajah", "human"))
                                .add_choice(dpp::command_option_choice("bot doang", "bot"))

                        )
                        .add_option(
                            dpp::command_option(dpp::co_string, "nama_channel", "(OPSIONAL) nama custom channelny, kalo ga di isi ngikut default", false)
                        )
                )

                .add_option(
                    dpp::command_option(dpp::co_sub_command, "remove", "nonaktifkan fitur member count")
                        .add_option(
                            dpp::command_option(dpp::co_string, "mode", "jenis channel yg mw dihapus", true)
                                .add_choice(dpp::command_option_choice("all members", "members"))
                                .add_choice(dpp::command_option_choice("yg human ajah", "human"))
                                .add_choice(dpp::command_option_choice("bot", "bot"))

                        )
                )
                .add_option(
                    dpp::command_option(dpp::co_sub_command, "edit", "edit namany")
                        .add_option(
                            dpp::command_option(dpp::co_string, "mode", "jenis member yang dihitung", true)
                                .add_choice(dpp::command_option_choice("semua members", "members"))
                                .add_choice(dpp::command_option_choice("human ajah", "human"))
                                .add_choice(dpp::command_option_choice("bot doang", "bot"))

                        )
                        .add_option(dpp::command_option(dpp::co_string, "nama", "nama barunya..", true))
                )
                .add_option(
                    dpp::command_option(dpp::co_sub_command, "sync", "sinkronisasi & update semua channel")
                )
                .set_default_permissions(dpp::p_administrator)
            },

            {"7", dpp::slashcommand("sync_guild", "sinkron config/setting guild", 0)
                .set_default_permissions(dpp::p_administrator)
            }

        };
};


#endif // COMMANDS_H
