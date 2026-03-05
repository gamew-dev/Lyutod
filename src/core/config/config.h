/**
 * Config.h

 * @brief Configuration manager for the bot.
 *
 * The Config class provides static methods, function, and paths for
 * configs, memory, history, and server setting.
 *
 * Responsibilities include:
 * - load client(bot) configs: tokens, version, etc.
 * - updating and reading user memory and server history for chatbot sessions
 * - manage guild-specific configurations
 *
 * @note All members are static since configuration is shared across the program.
 * @author Hissats
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include <filesystem>

#include "dpp/dpp.h"


/// Client config struct
//  The struct that store bot information
//  currently has no use????
struct CC {
    std::string botOwner,
                botToken,
                //botVersion,

                gptToken;

    bool isLog;
};


/// Guild config struct
//  The GC struct (Guild Config) stores guild-specific data such as
//  IDs, owner information, member count channel, and auto-role settings.
struct GC {
    std::string name;
    dpp::snowflake id,
                ownerID;

    bool autoRoleEnabled;
    std::string autoRoleName;
    dpp::snowflake autoRoleID;

    dpp::snowflake memberCountChannel1,
                   memberCountChannel2,
                   memberCountChannel3;

    dpp::snowflake loggerChannel;

};



class Config
{

    private:

    /// File/directory path
    static inline std::string clientPath = "data/client/config.json",
                              userPath   = "data/ai/user/",
                              serverPath = "data/ai/server/",
                              guildPath  = "data/guild/";

    public:

    static inline bool isShutingDown = false;
    static inline bool cooldownBsok = false;

    static inline std::string botOwner,
                              botToken,
                              //botVersi,
                              gptToken;
    static inline bool isLog;

    /// Bot config
    static bool clientLoadConfig();

    /// User chatbot memory
    static void userUpdateMemory(const std::string& id,
                                 const std::string& memory);
    static std::string userReadMemory(const std::string id);

    /// Server chatbot history
    static void serverUpdateHistory(const std::string& id,
                                    const std::vector<std::string>& history);
    static std::vector<std::string> serverReadMemory(const std::string id);

    /// Server config
    static std::vector<std::string> guildGetList();
    static bool guildCreateConfig(const dpp::guild_create_t& event);
    static void guildRemoveConfig(const std::string& guild_id),
                guildSaveAutoRole(const std::string& guild_id,
                                  const bool&        autorole,
                                  const dpp::snowflake& role_id),
                guildMemberCount (const std::string& guild_id,
                                  const short& pil,
                                  const dpp::snowflake& channel_id);


    /// Server sync guild
    //  sync database with server
    static void syncGuildConfig(dpp::cluster& bot, const std::string& guild_id, const dpp::snowflake& channel_id = 0);

    /// Server config getter
    //  i need to find an other way
    //  TODO: develop better implementation
    static GC guildLoadConfig(const std::string& guild_id);
};

#endif // CONFIG_H
