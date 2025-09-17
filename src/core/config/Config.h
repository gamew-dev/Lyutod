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

#include "dpp/dpp.h"


/// Guild config struct
//  The GC struct (Guild Config) stores guild-specific data such as
//  IDs, owner information, and auto-role settings.
struct GC {
    std::string name;
    dpp::snowflake id,
                ownerID;

    bool autoRoleEnabled;
    std::string autoRoleName;
    dpp::snowflake autoRoleID;

    bool memberCountEnabled;
    int memberCount;

    //todo: membercount channel id array
};



class Config
{

    private:

    /// File/directory path
    static inline std::string clientPath = "data/client/config.json";
    static inline std::string userPath = "data/ai/user/";
    static inline std::string serverPath = "data/ai/server/";
    static inline std::string guildPath = "data/guild/";

    public:

    static inline bool isShutingDown = false;
    static inline bool cooldownBsok = false;

    static inline std::string botOwner,
                              botToken,
                              botVersi,
                              gptToken;

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
    static bool guildCreateConfig(const dpp::guild_create_t& event);
    static void guildRemoveConfig(const std::string& guild_id),
                guildSaveAutoRole(const std::string& guild_id,
                                  const bool&        autorole,
                                  const dpp::snowflake& role_id),
                guildMemberCount (const std::string& guild_id);

    /// Server config getter
    //  i need to find an other way
    //  TODO: develop better implementation
    static GC guildLoadConfig(const std::string& guild_id);
};

#endif // CONFIG_H
