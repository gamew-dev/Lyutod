#include "base_commands.h"

void Commands::command_member_count(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    std::cout << "[Debug]: " << "checking parameter value..." << std::endl;
    auto subcommand = cmd_data.options[0];
    //std::cout << "[Debug]: " << "parameter value: " << subcommand << std::endl;

    if (subcommand.name == "add") {
        std::cout << "[Debug]: " << "True selected" << std::endl;

        std::string mode = std::get<std::string>(event.get_parameter("mode"));
        std::string channelName;
        if (event.get_parameter("nama_channel").index() != 0) {
            channelName = std::get<std::string>(event.get_parameter("nama_channel"));
        } else {
            channelName = std::get<std::string>(event.get_parameter("mode")) + ": 999";
        }

        // logic: enable fitur + simpan mode & channel
        std::cout << "[DEBUG] member count diaktifkan dengan mode " << mode << "   | channel: " << channelName << std::endl;
        event.reply("[DEBUG] member count diaktifkan dengan mode " + mode + " dan channel: " + channelName);


    }
    else if (subcommand.name == "remove") {
        std::cout << "[Debug]: " << "False selected" << std::endl;
        event.reply("[DEBUG] member count dinonaktifkan");
    }
}

