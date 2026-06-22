#include "base_commands.h"
#include <dpp/dpp.h>


void commands::command_autorole(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    event.thinking();

    dpp::command_interaction cmd_data = event.command.get_command_interaction();


    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    /// getter sub command option (set, edit, remove)
    //  and global variable for guild config, id etc
    auto subcommand = cmd_data.options[0];
    dpp::snowflake guild_id = event.command.guild_id;
    auto data = Config::guildLoadConfig(std::to_string(guild_id));

    if (subcommand.name == "set") {
        // add logic
        if (data.autoRoleEnabled) {
            event.edit_response("Autorole sudah aktif di server ini, gunakan `autorole edit` untuk mengubahnya");
            return;
        }

        dpp::snowflake role = std::get<dpp::snowflake>(event.get_parameter("role"));
        event.edit_response("autorole berhasil diaktifkan dengan role: <@&" + std::to_string(role) + ">.");
        Config::guildSaveAutoRole(std::to_string(guild_id), true, role);

    }

    else if (subcommand.name == "edit") {
        // edit logic
        dpp::snowflake role = std::get<dpp::snowflake>(event.get_parameter("role"));
        event.edit_response("autorole berhasil diubah dengan role: <@&" + std::to_string(role) + ">.");
        Config::guildSaveAutoRole(std::to_string(guild_id), true, role);

    }

    else if (subcommand.name == "disable") {
        // remove logic
        if (!data.autoRoleEnabled) {
            event.edit_response("tidak ditemukan autorole aktif di server ini");
            return;
        }
        event.edit_response("autorole berhasil dinonaktifkan");
        Config::guildSaveAutoRole(std::to_string(guild_id), false, 0);
    }
}
