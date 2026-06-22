/**
 * base_commands.h

 * @brief Declaration of slashcommand.
 *
 * The base commands file store the declaration of slashcommand and the function
 *
 *
 * @note Every command has it own implementation files
 * @author Hissats
 *
 */

#ifndef COMMANDS_H
#define COMMANDS_H

#include "../core/config.h"
#include "../services/responses_chat.h"


#include <map>

namespace dpp{
    struct slashcommand_t;
    struct slashcommand;
    class cluster;
}

namespace commands {

    void command_bot    (    const std::time_t& start,
                                   dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_server  (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_say     (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_autorole(          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_user    (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_census  (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_guild   (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event),
        command_chatbot (          dpp::cluster& bot,
                             const dpp::slashcommand_t& event);

    extern std::map<std::string, dpp::slashcommand> commands_list;
}


#endif // COMMANDS_H
