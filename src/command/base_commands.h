/**
 * base_commands.h

 * @brief Declaration of slashcommand.
 *
 * The base commands file store the declaration of slashcommand and the function
 *
 *
 * @note Every command has it own implementation files
 * @author Hissats
 *
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "dpp/dpp.h"
#include "Config.h"
#include "Responses.h"
#include "Utils.h"

class Commands {

    public:
    static void command_bot(         const std::time_t& start,
                                           dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_server (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_say         (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_autorole(      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_user   (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_census(      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event),
                command_guild  (      dpp::cluster& bot,
                                     const dpp::slashcommand_t& event);

    static inline std::map<std::string, dpp::slashcommand> commands_list {
        {"1", dpp::slashcommand("bot", "Info bot", 0)
            .add_option(dpp::command_option(dpp::co_sub_command, "status", "cek status bot"))
            .add_option(dpp::command_option(dpp::co_sub_command, "invite", "inpit banh"))
            .add_option(dpp::command_option(dpp::co_sub_command, "info", "ingfokan"))

        },

        {"2", dpp::slashcommand("server", "Command umum untuk server", 0)
            .add_option(dpp::command_option(dpp::co_sub_command, "info", "informasi server inih"))
            .add_option(dpp::command_option(dpp::co_sub_command, "icon", "gambar pp server inih"))
        },

        {"3", dpp::slashcommand("say", "Bot says icixiwir echo", 0)
            .add_option(dpp::command_option(dpp::co_string, "pesan", "textny..", true))
            .add_option(dpp::command_option(dpp::co_channel, "channel", "Channel tujuan", true))
        },

        {"4", dpp::slashcommand("autorole", "setting autorole server", 0)
            .add_option(dpp::command_option(dpp::co_sub_command, "set", "aktifkan autorole")
                .add_option(dpp::command_option(dpp::co_role, "role", "pilih role", true))
            )
            .add_option(dpp::command_option(dpp::co_sub_command, "edit", "edit role autorole")
                .add_option(dpp::command_option(dpp::co_role, "role", "pilih role", true))
            )
            .add_option(dpp::command_option(dpp::co_sub_command, "disable", "matiin autorole")

            )
            .set_default_permissions(dpp::p_administrator)
        },

        {"5", dpp::slashcommand("user", "command untuk user", 0)
            .add_option(dpp::command_option(dpp::co_sub_command, "info", "cek info user")
                .add_option(dpp::command_option(dpp::co_user, "user", "pilih", false))

            )
            .add_option(dpp::command_option(dpp::co_sub_command, "avatar", "cek pp user")
                .add_option(dpp::command_option(dpp::co_user, "user", "pilih", true))

            )
        },

        {"6", dpp::slashcommand("sensus", "setting channel sensus jumlah member", 0)
            .add_option(
                dpp::command_option(dpp::co_sub_command, "add", "aktifkan sensus count")
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
                dpp::command_option(dpp::co_sub_command, "remove", "nonaktifkan fitur sensus count")
                    .add_option(
                        dpp::command_option(dpp::co_string, "mode", "jenis channel yg mw dihapus", true)
                            .add_choice(dpp::command_option_choice("all members", "members"))
                            .add_choice(dpp::command_option_choice("yg human ajah", "human"))
                            .add_choice(dpp::command_option_choice("bot", "bot"))

                    )
            )
            .add_option(
                dpp::command_option(dpp::co_sub_command, "edit", "edit nama channel")
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

        {"7", dpp::slashcommand("guild", "command untuk guild khusus atmint", 0)
            .add_option(
                dpp::command_option(dpp::co_sub_command, "sync", "sinkronisasi database dengan pusat")
            )
            .set_default_permissions(dpp::p_administrator)
        }

    };
};


#endif // COMMANDS_H
