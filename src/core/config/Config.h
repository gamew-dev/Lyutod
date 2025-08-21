#ifndef CONFIG_H
#define CONFIG_H

#include "dpp/dpp.h"

class Config
{

    private:


    static inline std::string clientPath = "data/client/config.json";
    static inline std::string guildPath = "data/guild/";

    public:

    static inline std::string autoRoleID = "",
                              autoRoleName = "",
                              ownerID = "",
                              ownerName = "",
                              guildID = "",
                              guildName = "";

    static inline bool autoRoleEnabled = false;

    static void clientLoadConfig (),
                clientSaveConfig ();

    static void guildCreateConfig(const std::string& guild_id),
                guildRemoveConfig(const std::string& guild_id),
                guildSaveConfig  (const std::string& guild_id);

    static nlohmann::json guildLoadConfig(const std::string& guild_id);
};

#endif // CONFIG_H
