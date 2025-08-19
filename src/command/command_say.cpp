#include "base_commands.h"

void Commands::command_say( dpp::cluster& bot, const dpp::slashcommand_t& event) {

    std::string pesan = std::get<std::string>(event.get_parameter("pesan"));
    dpp::snowflake channel_id = std::get<dpp::snowflake>(event.get_parameter("channel"));

    bot.message_create(dpp::message(channel_id, pesan).set_allowed_mentions(true,false,false,true));

    event.reply(
        dpp::message("don, cona cek <#" + std::to_string(channel_id) + ">.")
        .set_flags(dpp::m_ephemeral)
    );

}
