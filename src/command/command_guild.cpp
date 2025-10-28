#include "base_commands.h"

void Commands::command_guild(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    std::string guild_id_str = std::to_string(event.command.guild_id);
    std::string channel_id_str = std::to_string(event.command.channel_id);

    /// getter sub command option (set, edit, remove)
    //  and global variable for guild config, id etc
    auto subcommand = cmd_data.options[0];

    if (subcommand.name == "sync") {


        //event.reply("membuka database server/guild...");

        Config::syncGuildConfig(bot, guild_id_str, channel_id_str);
    }

    else if (subcommand.name == "logger") {
        std::string mode = std::get<std::string>(event.get_parameter("mode"));

        auto data = Config::guildLoadConfig(guild_id_str);

        if (mode == "add") {
            event.reply("add, no effect");
            return;
        }

        else if (mode == "remove") {
            event.reply("remove, no effect");
            return;

        }

    }


}
