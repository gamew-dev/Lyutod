#include "Config.h"


void Config::clientLoadConfig() {

    std::ifstream file(clientPath);
    if (file) {
        std::cout << "[INFO] Reading bot config..." <<std::endl;
        nlohmann::json fileJson;
        file >> fileJson;
        botOwner = fileJson.value("botOwner", "");

    }
    else {
        std::cout << "[INFO] Creating new bot config..." << std::endl;
        clientSaveConfig();
    }

}

void Config::clientSaveConfig() {

    nlohmann::json filejson;
    filejson["botOwner"] = "";

    std::ofstream file(clientPath);
    file << filejson.dump(4);

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
