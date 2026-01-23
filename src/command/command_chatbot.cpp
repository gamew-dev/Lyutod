#include "base_commands.h"

void Commands::command_chatbot (dpp::cluster& bot, const dpp::slashcommand_t& event) {

    event.thinking();

    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    std::string guild_id_str = std::to_string(event.command.guild_id);
    std::string user_id_str = std::to_string(event.command.usr.id);
    /// getter sub command option (set, edit, remove)
    //  and global variable for guild config, id etc
    auto subcommand = cmd_data.options[0];

    if (subcommand.name == "check_memory") {

        std::cout << "pemanggilan fungsi memory..." << std::endl;
        std::string memory = Config::userReadMemory(user_id_str);
        if (memory == "") memory = "Anda belum memiliki history memory";
        std::cout << "memory yang didapat: "<< memory << std::endl;
        event.edit_response("```" + memory + "```");
        std::cout << "edit respon/jawab" << std::endl;
    }



    else if (subcommand.name == "history") {

        std::cout << "ambil data history" << std::endl;
        std::vector<std::string> history = Config::serverReadMemory(guild_id_str);

        std::string result;
        for (const auto& line : history) {
            std::string display = line;

            if (display.rfind("[anda]:", 0) == 0) {
                display.replace(0, 7, "[Lyudya]:");
            }

            result += display + "\n";
            std::cout << "cek history line: " << line << std::endl;
        }
        event.edit_response("```" + result + "```");
        std::cout << "edit respon/jawab" << std::endl;
    }

}
