#ifndef CONFIG_H
#define CONFIG_H

#include "dpp/dpp.h"

class Config
{
    public:

    static inline std::string path = "src/core/config/config.json";

    static inline std::string autoRoleID = "",
                              autoRoleName = "",
                              ownerID = "",
                              ownerName = "",
                              guildID = "",
                              guildName = "";

    static inline bool autoRoleEnabled = false;

    static void loadConfig(),
                saveConfig();
};

#endif // CONFIG_H
