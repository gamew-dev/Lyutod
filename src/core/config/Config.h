#ifndef CONFIG_H
#define CONFIG_H

#include "dpp/dpp.h"

struct GC {
    std::string name ,
                id,
                ownerID;

    bool autoRoleEnabled;
    std::string autoRoleName,
                autoRoleID;

};



class Config
{

    private:


    static inline std::string clientPath = "data/client/config.json";
    static inline std::string userPath = "data/ai/user/";
    static inline std::string serverPath = "data/ai/server/";
    static inline std::string guildPath = "data/guild/";

    public:

    static inline std::string botOwner,
                              botToken,
                              botVersi,
                              gptToken;

    static bool clientLoadConfig();

    static void userUpdateMemory(const std::string id, const std::string memory);
    static std::string userReadMemory(const std::string id);

    static void serverUpdateMemory(const std::string id, const std::string memory);
    static std::vector<std::string> serverReadMemory(const std::string id);

    static bool guildCreateConfig(const dpp::guild_create_t& event);
    static void guildRemoveConfig(const std::string& guild_id),
                guildSaveAutoRole(const std::string& guild_id,
                                  const bool&        autorole,
                                  const std::string& role_id);

    static GC guildLoadConfig(const std::string& guild_id);
};

#endif // CONFIG_H
