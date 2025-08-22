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
    static inline std::string guildPath = "data/guild/";

    public:

    static inline std::string botOwner = "";

    static void clientLoadConfig (),
                clientSaveConfig ();

    static bool guildCreateConfig(const dpp::guild_create_t& event);
    static void guildRemoveConfig(const std::string& guild_id),
                guildSaveConfig  (const std::string& guild_id);

    static GC guildLoadConfig(const std::string& guild_id);
};

#endif // CONFIG_H
