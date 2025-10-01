#include "base_commands.h"

void Commands::command_guild(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    /// getter sub command option (set, edit, remove)
    //  and global variable for guild config, id etc
    auto subcommand = cmd_data.options[0];

    if (subcommand.name == "sync") {
        std::string guild_id = std::to_string(event.command.guild_id);
        std::string channel_id = std::to_string(event.command.channel_id);

        event.reply("membuka database server/guild...");

        Config::syncGuildConfig(bot, guild_id, channel_id);
    }


}
