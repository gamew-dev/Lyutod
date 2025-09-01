#include "base_commands.h"

void Commands::command_set_autorole(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::snowflake guild_id = event.command.guild_id;

    std::cout << "[DEBUG] Getting set value" << std::endl;
    bool autorole = std::get<bool>(event.get_parameter("set"));
    std::cout << "[DEBUG] Set value: "<< autorole << std::endl;


    std::cout << "[DEBUG] Getting role value" << std::endl;
    dpp::snowflake role;
    auto param = event.get_parameter("role");

    if (param.index() == 0) {
        role = 0;
    } else {
        role = std::get<dpp::snowflake>(event.get_parameter("role"));
    }

    std::cout << "[DEBUG] role value: "<< std::to_string(role) << std::endl;


    if (!autorole) {
        event.reply("Autorole berhasil **dinonaktifkan**.");
        role = 0;
    }

    else if (autorole && role == 0) {
        event.reply("Anda harus memilih **role** untuk mengaktifkan autorole.");
        return;
    }

    else if (autorole && role != 0) {
        event.reply("Autorole berhasil diaktifkan dengan role: <@&" + std::to_string(role) + ">.");
    }

    Config::guildSaveAutoRole(std::to_string(guild_id), autorole, std::to_string(role));
    std::cout << "[DEBUG] End of line" << std::endl;
}
