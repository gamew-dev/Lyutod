#include "base_commands.h"

void Commands::command_status(const std::time_t& start, dpp::cluster& bot, const dpp::slashcommand_t& event) {
    std::string title = "Lyudya " + Responses::emoteReact();
    dpp::embed status = dpp::embed()
        .set_color(dpp::colors::red_blood)
        .set_title(title)
            //.set_url("https://dpp.dev/")
            //.set_author("Some name", "https://dpp.dev/", "https://dpp.dev/DPP-Logo.png")
        .set_thumbnail("https://cdn.discordapp.com/attachments/1270735248472277004/1370083493148889210/29605-omg.gif?ex=681e352f&is=681ce3af&hm=18c7e82976d7eb6f27d1a728a33b9e5b0836f04db224cb3dffde3d471ef0e100&")
        .set_description("Bot random gabut over engineered")

        .add_field(
                "Status..",
                "🟢 healthy"
        )

        .add_field(
                "Uptime Bot",
                Utils::getTime(start)
        )
        .add_field(
                "Latency",
                Utils::getPing(bot),
                true
        )
        .add_field(
                "Memory",
                Utils::getRam(),
                true
        )
        //.set_image("https://dpp.dev/DPP-Logo.png")
        .set_footer(
            dpp::embed_footer()
            .set_text("Version: 0.6 [25M7D19]")
            .set_icon("https://cdn.discordapp.com/attachments/1270735248472277004/1370083495313145916/42802-givelove.png?ex=681e3530&is=681ce3b0&hm=dde61ba938af5ce6e8934dfd54b023570c983a1bfdb944d56adcaa2c838d6595&")
        )

        .set_timestamp(time(0));



    dpp::message msg(event.command.channel_id, status);


    event.reply(msg);


}
