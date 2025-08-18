#include "Config.h"

void Config::loadConfig() {

    std::ifstream file(path);
    if (file) {
        std::cout << "reading bot config..." <<std::endl;
        nlohmann::json fileJson;
        file >> fileJson;
        ownerID = fileJson.value("ownerID", "");
        ownerName = fileJson.value("ownerName", "");
        guildID = fileJson.value("guildID", "");
        guildName = fileJson.value("guildName", "");
        autoRoleID = fileJson.value("autoRoleID", "");
        autoRoleName = fileJson.value("autoRoleName", "");
        autoRoleEnabled = fileJson.value("autoRoleEnabled", false);

    }
    else {
        std::cout << "creating new bot config..." << std::endl;
        saveConfig();
    }

}

void Config::saveConfig() {

    nlohmann::json filejson;
    filejson["ownerID"] = ownerID;
    filejson["ownerName"] = ownerName;
    filejson["guildID"] = guildID;
    filejson["guildName"] = guildName;
    filejson["autoRoleID"] = autoRoleID;
    filejson["autoRoleEnabled"] = autoRoleEnabled;
    filejson["autoRoleName"] = autoRoleName;
    std::ofstream file(path);
    file << filejson.dump(4);

}
