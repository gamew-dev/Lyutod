#include "base_commands.h"

void Commands::command_sync_guild(dpp::cluster& bot, const dpp::slashcommand_t& event) {
    std::string guild_id = std::to_string(event.command.guild_id);
    std::string channel_id = std::to_string(event.command.channel_id);

    event.reply("membuka database server/guild...");

    Config::syncGuildConfig(bot, guild_id, channel_id);
}
