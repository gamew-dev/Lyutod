#include "base_commands.h"

void Commands::command_server_info (dpp::cluster& bot, const dpp::slashcommand_t& event) {

    std::string owner = dpp::user().get_mention(event.command.get_guild().owner_id);
    std::string id = std::to_string(event.command.guild_id);

    uint64_t timestamp = static_cast<uint64_t>(event.command.get_guild().get_creation_time());
    std::string created = "<t:" + std::to_string(timestamp) + "> " + "<t:" + std::to_string(timestamp) + ":R>";

    dpp::embed status = dpp::embed()
        .set_color(dpp::colors::antique_bronze)
        .set_title(event.command.get_guild().name)
        .set_url("https://discord.gg/ntStxHH9gS")
        //.set_author("Server Invite", "https://discord.gg/ntStxHH9gS", event.command.get_guild().icon)
        //.set_thumbnail(event.command.get_guild().icon)
        .set_description(event.command.get_guild().description)

        .add_field(
            "Server Owner",
            owner,
            true
        )

        .add_field(
            "Server ID",
            id,
            true
        )


        .add_field(
            "Member",
            std::to_string(event.command.get_guild().member_count)
        )

        .add_field(
            "Created",
            created
        )

        .set_footer(
            dpp::embed_footer()
            .set_text("Lyudya bot")
            .set_icon("https://cdn.discordapp.com/attachments/1270735248472277004/1370083495313145916/42802-givelove.png?ex=681e3530&is=681ce3b0&hm=dde61ba938af5ce6e8934dfd54b023570c983a1bfdb944d56adcaa2c838d6595&")
        )

        .set_timestamp(time(0));

            /* Create a message with the content as our new embed. */
        dpp::message msg(event.command.channel_id, status);

            /* Reply to the user with the message, containing our embed. */
        event.reply(msg);

}
