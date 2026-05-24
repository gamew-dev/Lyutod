/**
 * Config.h

 * @brief Configuration manager for the bot.
 *
 * The Config class provides  methods, function, and paths for
 * configs, memory, history, and server setting.
 *
 * Responsibilities include:
 * - load client(bot) configs: tokens, version, etc.
 * - updating and reading user memory and server history for chatbot sessions
 * - manage guild-specific configurations
 *
 * @note All members are  since configuration is shared across the program.
 * @author Hissats
 *
 */

#ifndef CONFIG_H
#define CONFIG_H

#include "shared/data.h"

#include <string> // std::string
#include <vector> // std::vector


namespace dpp {
class cluster;
struct guild_create_t;
}


namespace config
{

bool isLog = false;

    /// File/directory path
    std::string clientPath = "data/client/config.json"  ,
                userPath   = "data/ai/user/"            ,
                serverPath = "data/ai/server/"          ,
                guildPath  = "data/guild/"              ;


    /// Bot config
    BotConfig LoadBotConfig();

    /// User chatbot memory
    void UserUpdateMemory(const std::string& id,
                                 const std::string& memory);
    std::string UserReadMemory(const std::string id);

    /// Server chatbot history
    void ServerUpdateHistory(const std::string& id,
                                    const std::vector<std::string>& history);
    std::vector<std::string> ServerReadMemory(const std::string id);

    /// Server config
    std::vector<std::string> GuildGetList();

    bool GuildCreateConfig(const dpp::guild_create_t& event);

    void GuildRemoveConfig(const std::string& guild_id),

         GuildSaveAutoRole(const std::string& guild_id,
                           const bool&        autorole,
                           const u_int64_t& role_id),

         GuildMemberCount (const std::string& guild_id,
                           const short& pil,
                           const u_int64_t& channel_id);


    /// Server sync guild
    //  sync database with server
     void SyncGuildConfig(dpp::cluster& bot,
                          const std::string& guild_id,
                          const u_int64_t& channel_id = 0);

    /// Server config getter
    //  i need to find an other way
    //  TODO: develop better implementation
     //GC guildLoadConfig(const std::string& guild_id);
}

#endif // CONFIG_H
