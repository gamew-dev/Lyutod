/**
 *  Config.cpp
 *
 *  @brief Implementation of static class Config
 *
 *  This file defines functions to process and assign each input accordingly.
 *
 *  @author Hissats
 */

#include "config.h"

#include <dpp/dpp.h>
#include <filesystem>

namespace config {

/**
*   ClientLoadConfig
*
*   Load the bot config, if found and valid then load and return true
*   While the file nowhere to be found then create new one and return
*   false which mean terminate the program
*   See also: main.cpp
*
*/
BotConfigStructData LoadBotConfig() {

    namespace fs = std::filesystem;

    BotConfigStructData _config;

    fs::create_directories(userPath);
    fs::create_directories(serverPath);
    fs::create_directories(guildPath);

    std::ifstream file(clientPath);

    if (!file) {
        std::cout << "eror membaca file";

        _config.valid = false;
        return _config;
    }

    nlohmann::json file_json_data;

    if (file) {

        try {
            file >> file_json_data;
        } catch (const json::parse_error& e) {
            std::cout << "eror parse config.json: " << e.what() << '\n';
            _config.valid = false;
            return _config;
        }

        std::cout << "[INFO] Reading bot config..." <<std::endl;

        /// --- BOT -----------------------------------------

        if (j.contains("bot")) {
            const auto& bot = j["bot"];
            _config.owner_id          = bot.value("owner_id", "");
            _config.bot_token         = bot.value("token", "");
            _config.version           = bot.value("version", "");
            _config.log_enabled       = bot.value("log_enabled", false);
            _config.status_channel_id = bot.value("status_channel_id", "");
        }

        /// --- BOT -----------------------------------------

        if (j.contains("ai")) {
            const auto& ai = j["ai"];
            _config.chat_enabled    = ai.value("enabled", false);
            _config.ai_token        = ai.value("token", "");
            //_config.ai.active_provider = ai.value("active_provider", "");
            //_config.ai.active_model    = ai.value("active_model", "");

            /*

            if (ai.contains("providers") && ai["providers"].contains(_config.ai.active_provider)) {
                const auto& provider = ai["providers"][_config.ai.active_provider];
                _config.ai.base_url = provider.value("base_url", "");

                if (provider.contains("models")) {
                    for (const auto& [alias, model_json] : provider["models"].items()) {
                        _config.ai.models[alias] = ParseModel(model_json);
                    }
                }
            }

            // memory & history
            if (ai.contains("memory")) {
                _config.ai.memory_max_items = ai["memory"].value("max_items", 20);
                _config.ai.memory_dedup     = ai["memory"].value("dedup_enabled", true);
            }
            if (ai.contains("history")) {
                _config.ai.history_max_items = ai["history"].value("max_items", 10);
            }

            */
        }

        /// --- Feature -----------------------------------------
            if (j.contains("features")) {
                const auto& f = j["features"];
                _config.chat_enabled        = f.value("msg_chatbot", false);
                _config.commands_enabled    = f.value("slashcommand", false);
                _config.autorole_enabled    = f.value("autorole", false);
                _config.cencus_enabled      = f.value("census", false);
            }

            _config.valid = !cfg.bot_token.empty();
            return _config;



    }

}

/**
 *  userReadMemory
 *
 *  This function read external files for chatbot user memory. given by the parameter,
 *  the program automatically search based on the id, if there was none to be found it
 *  will return empty string and create a new file
 *
 *  @param user id
 *  @return user id memory string
 *
 */

std::string UserReadMemory(const std::string id) {

    std::string path = userPath + id + ".json";
    std::string memory;

    std::ifstream file(path);
    if (file) {
        if (isLog) std::cout << "[INFO] Reading user memory for: "<< id <<std::endl;

        nlohmann::json fileJson;
        file >> fileJson;
        memory = fileJson.value("memory", "");
    }
    else {
        if (isLog) std::cout << "[INFO] Creating user memory for: "<< id << std::endl;
        nlohmann::json filejson;
        filejson["memory"] = "";

        std::ofstream out(path);
        out << filejson.dump(4);

        memory = "";
    }

    return memory;
}

/**
 *  userUpdateMemory
 *
 *  As the name subject, this methods update the user memory. The program would
 *  overwrite the old memory
 *
 *  @param user id
 *  @param user memory
 *
 */

void UserUpdateMemory(const std::string& id,
                              const std::string& memory) {

    std::string path = userPath + id + ".json";

    std::ifstream file(path);

    nlohmann::json filejson;

    if (file.is_open()) {
        file >> filejson;
        file.close();
    }
    else {
        if (isLog) std::cout << "[ERROR] no user memory found for: " << id << std::endl;
        return;
    }

    filejson["memory"] = memory;

    std::ofstream out(path);
    out << filejson.dump(4);
    out.close();

}

/**
 *  serverReadMemory
 *
 *  Same as userRead, but with vector/array of string. Each server only has 1 file,
 *  while dm chatbot use the user id for server id
 *
 *  @param server id
 *  @return server id history string vector
 *
 */

std::vector<std::string> ServerReadMemory(const std::string id) {

    std::string path = serverPath + id + ".txt";
    std::vector<std::string> history;

    std::ifstream file(path);
    if (file) {
        if (isLog) std::cout << "[INFO] Reading server history for: " << id << std::endl;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                history.push_back(line);
            }
        }
    } else {
        if (isLog) std::cout << "[INFO] Creating server history for: " << id << std::endl;
        std::ofstream out(path);
        history.push_back("---End of History---");
        // file baru -> kosong
    }

    return history;
}

/**
 *  serverUpdateHistory
 *
 *  Work the same as userUpdate...
 *
 *  @param server id
 *  @param server chat history
 *
 */

void ServerUpdateHistory(const std::string& id, const std::vector<std::string>& history) {
    std::string path = serverPath + id + ".txt";
    std::ofstream out(path);
    if (out) {
        for (const auto& line : history) {
            out << line << "\n";
        }
    }
}

/**
 *  guildCreateConfig
 *
 *  Called when bot invited to new server or bot startup, bot will run a lop for every server
 *  or guild that it joined. If the filename already exist it would just return and will be skipped
 *  However, if the file is none to be found or, the bot just joined a new server of course...
 *  it will create a new file
 *
 *  @param guild create event
 *
 */

std::vector<std::string> GuildGetList() {
    std::vector<std::string> guildList;

    for (const auto& entry : std::filesystem::directory_iterator(guildPath)) {
        if (entry.is_regular_file() && entry.path().extension() == ".json") {
            guildList.push_back(entry.path().stem().string());

        }
    }

    return guildList;
}


bool GuildCreateConfig(const dpp::guild_create_t& event) {

    dpp::snowflake id = event.created.id;
    std::string idstr = std::to_string(id);
    std::string name = event.created.name;
    std::string path = guildPath + idstr + ".json";

    std::ifstream file(path);
    if(file.good()) {
        if (isLog) std::cout << "[ + ] " << name << " is ready\n";
        return false;
    }
    else {

        std::string owner = std::to_string(static_cast<uint64_t>(event.created.owner_id));

        nlohmann::json filejson;

        filejson["Name"] = name;
        filejson["ID"] = idstr;
        filejson["ownerID"] = owner;

        filejson["autoRoleEnabled"] = false;
        filejson["autoRoleName"] = "";
        filejson["autoRoleID"] = "0";

        filejson["memberCountChannel1"] = "0";
        filejson["memberCountChannel2"] = "0";
        filejson["memberCountChannel3"] = "0";

        filejson["loggerChannel"] = "0";


        std::ofstream file(path);
        file << filejson.dump(4);

        if (isLog) std::cout << "[ + ] Creating config: " << id << std::endl;

        return true;
    }
}

/**
 *  guildSaveAutoRole
 *
 *  A function to be paired with autorole command, pretty much self explanotary
 *  @TODO: find a better way
 *
 *  @param guild id
 *  @param is autorole enabled? dunno lol
 *  @param the role selected id
 *
 */

void GuildSaveAutoRole(const std::string& guild_id,
                               const bool& autorole,
                               const dpp::snowflake& role_id) {

    std::string path = guildPath + guild_id + ".json";


    std::ifstream file(path);

    nlohmann::json filejson;

    if (file.is_open()) {
        file >> filejson;
        file.close();
    }
    else {
        if (isLog) std::cout << "[ERROR] no guild config file found for: " << guild_id << std::endl;
        return;
    }

    std::string role_id_str = std::to_string(role_id);
    std::string role_name = "<@" + role_id_str + ">";

    filejson["autoRoleEnabled"] = autorole;
    filejson["autoRoleID"] = role_id_str;
    filejson["autoRoleName"] = role_name;

    std::ofstream out(path);
    out << filejson.dump(4);
    out.close();

}


void GuildMemberCount(const std::string& guild_id, const short& pil, const dpp::snowflake& channel_id) {

    std::string path = guildPath + guild_id + ".json";

    if (isLog) std::cout << "[Debug]: parameter value...\n" << "\tguild_id: " << guild_id << "\n\tpil: " << pil << "\n\tchannel_id: " << channel_id << std::endl;

    std::ifstream file(path);

    nlohmann::json fileJson;

    if (file.is_open()) {
        file >> fileJson;
        file.close();
    }
    else {
        if (isLog) std::cout << "[ERROR] no guild config file found for: " << guild_id << std::endl;
        return;
    }



    //fileJson["memberCount"] = 0; // probably gonna delete this
    //fileJson["memberCountEnabled"] = true; // and this

    if (pil == 1) {
        fileJson["memberCountChannel1"] = std::to_string(channel_id);
    }
    else if (pil == 2) {
        fileJson["memberCountChannel2"] = std::to_string(channel_id);
    }
    else if (pil == 3) {
        fileJson["memberCountChannel3"] = std::to_string(channel_id);
    }
    else if (pil == 4) {
        fileJson["memberCountChannel1"] = "0";
    }
    else if (pil == 5) {
        fileJson["memberCountChannel2"] = "0";
    }
    else if (pil == 6) {
        fileJson["memberCountChannel3"] = "0";
    }

    std::ofstream out(path);
    out << fileJson.dump(4);
    out.close();

    if (isLog) std::cout << "[Debug]: data saved" << std::endl;
}
/*
GC guildLoadConfig(const std::string& guild_id) {

    std::string path = guildPath + guild_id + ".json";
    GC data;

    std::ifstream file(path);
    if (file) {
        if (isLog) std::cout << "[INFO] Searching guild config..." <<std::endl;
        nlohmann::json fileJson;
        file >> fileJson;

        data.name = fileJson.value("Name", "");
        if (data.name != "") if (isLog) std::cout << "opening " << data.name << " config" << std::endl;
        data.id = std::stoull(fileJson.value("ID", "0"));
        data.ownerID = std::stoull(fileJson.value("ownerID", "0"));

        data.autoRoleEnabled = fileJson.value("autoRoleEnabled", false);
        data.autoRoleName = fileJson.value("autoRoleName", "");
        data.autoRoleID = std::stoull(fileJson.value("autoRoleID", "0"));

        data.memberCountChannel1 = std::stoull(fileJson.value("memberCountChannel1", "0"));
        data.memberCountChannel2 = std::stoull(fileJson.value("memberCountChannel2", "0"));
        data.memberCountChannel3 = std::stoull(fileJson.value("memberCountChannel3", "0"));

        data.loggerChannel = std::stoull(fileJson.value("loggerChannel", "0"));

    }

    return data;
}
*/

/*
void SyncGuildConfig(dpp::cluster& bot, const std::string& guild_id, const dpp::snowflake& channel_id) {

    std::string path = guildPath + guild_id + ".json";
    //std::string repl;
    GC data;
    nlohmann::json fileJson;

    std::ifstream file(path);
    if (file) {
        if (isLog) std::cout << "[INFO] Searching guild config..." <<std::endl;
        file >> fileJson;

        data.name = fileJson.value("Name", "");
        if (data.name != "") {
            if (isLog) std::cout << "Database server found" << std::endl;
            bot.message_create(dpp::message(channel_id, "data ditemukan untuk server " + data.name));
        }
        data.id = std::stoull(fileJson.value("ID", "0"));
        data.ownerID = std::stoull(fileJson.value("ownerID", "0"));
        data.autoRoleEnabled = fileJson.value("autoRoleEnabled", false);
        data.autoRoleName = fileJson.value("autoRoleName", "");
        data.autoRoleID = std::stoull(fileJson.value("autoRoleID", "0"));

        data.memberCountChannel1 = std::stoull(fileJson.value("memberCountChannel1", "0"));
        data.memberCountChannel2 = std::stoull(fileJson.value("memberCountChannel2", "0"));
        data.memberCountChannel3 = std::stoull(fileJson.value("memberCountChannel3", "0"));

        data.loggerChannel = std::stoull(fileJson.value("loggerChannel", "0"));

        file.close();
    } else {
        if (isLog) std::cout << "database server not found" << std::endl;
        bot.message_create(dpp::message(channel_id, "database server tidak ditemukan"));
        return;
    }

    fileJson["Name"] = data.name;
    fileJson["ID"] = std::to_string(data.id);
    fileJson["ownerID"] = std::to_string(data.ownerID);

    fileJson["autoRoleEnabled"] = data.autoRoleEnabled;
    fileJson["autoRoleName"] = data.autoRoleName;
    fileJson["autoRoleID"] = std::to_string(data.autoRoleID);

    fileJson["memberCountChannel1"] = std::to_string(data.memberCountChannel1);
    fileJson["memberCountChannel2"] = std::to_string(data.memberCountChannel2);
    fileJson["memberCountChannel3"] = std::to_string(data.memberCountChannel3);

    fileJson["loggerChannel"] = "0";

    bot.start_timer([&, channel_id](dpp::timer h) {
        bot.message_create(dpp::message(channel_id, "sinkronisasi data berhasil"));
        bot.stop_timer(h);
    }, 2);

    std::ofstream out(path);
    out << fileJson.dump(4);
    out.close();
}
*/
}
