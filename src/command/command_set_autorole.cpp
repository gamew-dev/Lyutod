#include "base_commands.h"

void Commands::command_set_autorole(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::snowflake guild_id = event.command.guild_id;

    std::cout << "[DEBUG] Getting set value" << std::endl;
    bool autorole = std::get<bool>(event.get_parameter("set"));
    std::cout << "[DEBUG] Set value: "<< autorole << std::endl;


    std::cout << "[DEBUG] Getting role value" << std::endl;
    dpp::role role;
    if (event.command.resolved.roles.find(std::get<dpp::snowflake>(event.get_parameter("role"))) != event.command.resolved.roles.end()) {
            role = event.command.resolved.roles.at(std::get<dpp::snowflake>(event.get_parameter("role")));
    }
    std::cout << "[DEBUG] role value: "<< role.get_mention() << std::endl;

     if (!autorole) {
        event.reply("Autorole berhasil **dinonaktifkan**.");
    }

    else if (autorole && role.id == 0) {
        event.reply("Anda harus memilih **role** untuk mengaktifkan autorole.");
    }

    else if (autorole && role.id != 0) {
        event.reply("Autorole berhasil diaktifkan dengan role: <@&" + std::to_string(role.id) + ">.");
    }
    event.reply("Womp womp.");
    std::cout << "[DEBUG] End of line" << std::endl;
}
