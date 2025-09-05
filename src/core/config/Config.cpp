#include "Config.h"


bool Config::clientLoadConfig() {

    std::ifstream file(clientPath);
    if (file) {
        std::cout << "[INFO] Reading bot config..." <<std::endl;
        nlohmann::json fileJson;
        file >> fileJson;
        botOwner = fileJson.value("botOwner", "");
        botToken = fileJson.value("botToken", "");
        botVersi = fileJson.value("botVersi", "");
        gptToken = fileJson.value("gptToken", "");

        return true;

    }
    else {
        std::cout << "[INFO] Creating new bot config..." << std::endl;
        nlohmann::json filejson;
        filejson["botOwner"] = "";
        filejson["botToken"] = "";
        filejson["botVersi"] = "";
        filejson["gptToken"] = "";

        std::ofstream file(clientPath);
        file << filejson.dump(4);

        return false;
    }

}

std::string Config::userReadMemory(const std::string id) {

    std::string path = userPath + id + ".json";
    std::string memory;

    std::ifstream file(path);
    if (file) {
        std::cout << "[INFO] Reading user memory for: "<< id <<std::endl;

        nlohmann::json fileJson;
        file >> fileJson;
        memory = fileJson.value("memory", "");
    }
    else {
        std::cout << "[INFO] Creating user memory for: "<< id << std::endl;
        nlohmann::json filejson;
        filejson["memory"] = "";

        std::ofstream out(path);
        out << filejson.dump(4);

        memory = "";
    }

    return memory;
}


void Config::userUpdateMemory(const std::string id,
                              const std::string memory) {

    std::string path = userPath + id + ".json";

    std::ifstream file(path);

    nlohmann::json filejson;

    if (file.is_open()) {
        file >> filejson;
        file.close();
    }
    else {
        std::cout << "[ERROR] no user memory found for: " << id << std::endl;
        return;
    }

    filejson["memory"] = memory;

    std::ofstream out(path);
    out << filejson.dump(4);
    out.close();

}

bool Config::guildCreateConfig(const dpp::guild_create_t& event) {

    ;
    std::string id = std::to_string(static_cast<uint64_t>(event.created.id));
    std::string name = event.created.name;
    std::string path = guildPath + id + ".json";

    std::ifstream file(path);
    if(file.good()) {
        std::cout << "[ + ] " << name << " is ready\n";
        return false;
    }
    else {

        std::string owner = std::to_string(static_cast<uint64_t>(event.created.owner_id));

        nlohmann::json filejson;

        filejson["Name"] = name;
        filejson["ID"] = id;
        filejson["ownerID"] = owner;

        filejson["autoRoleEnabled"] = false;
        filejson["autoRoleName"] = "";
        filejson["autoRoleID"] = "";



        std::ofstream file(path);
        file << filejson.dump(4);

        std::cout << "[ + ] Creating config: " << id << std::endl;

        return true;
    }
}

void Config::guildSaveAutoRole(const std::string& guild_id,
                               const bool& autorole,
                               const std::string& role_id) {

    std::string path = guildPath + guild_id + ".json";

    std::ifstream file(path);

    nlohmann::json filejson;

    if (file.is_open()) {
        file >> filejson;
        file.close();
    }
    else {
        std::cout << "[ERROR] no guild config file found for: " << guild_id << std::endl;
        return;
    }

    std::string role_name = "<@" + role_id + ">";

    filejson["autoRoleEnabled"] = autorole;
    filejson["autoRoleID"] = role_id;
    filejson["autoRoleName"] = role_name;

    std::ofstream out(path);
    out << filejson.dump(4);
    out.close();

}


GC Config::guildLoadConfig(const std::string& guild_id) {

    std::string path = guildPath + guild_id + ".json";
    GC data;

    std::ifstream file(path);
    if (file) {
        std::cout << "[INFO] Searching guild config..." <<std::endl;
        nlohmann::json fileJson;
        file >> fileJson;

        data.name = fileJson.value("Name", "");
        if (data.name != "") std::cout << "opening " << data.name << " config" << std::endl;
        data.id = fileJson.value("ID", "");
        data.ownerID = fileJson.value("ownerID", "");
        data.autoRoleEnabled = fileJson.value("autoRoleEnabled", false);
        data.autoRoleName = fileJson.value("autoRoleName", "");
        data.autoRoleID = fileJson.value("autoRoleID", "");

    }

    return data;
}

