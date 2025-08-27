#include "base_commands.h"

void Commands::command_set_autorole(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::snowflake guild_id = event.command.guild_id;

    bool autorole = std::get<bool>(event.get_parameter("set"));
}
