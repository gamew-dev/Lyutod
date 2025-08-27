#include "base_commands.h"

void Commands::command_user_info(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::user user;

    //event.get
    std::cout << "[Debug] Entering slash command func" << std::endl;

    auto param = event.get_parameter("user");
    std::cout << "[Debug] Checking user parameter" << std::endl;

    if (param.index() == 0) {

        user = event.command.usr;
        std::cout << "Debug: user id: self [" << std::to_string(user.id) << "]" << std::endl;
    } else {
        dpp::snowflake user_id = std::get<dpp::snowflake>(param);
        user = event.command.resolved.users.at(user_id);
        std::cout << "Debug: user id: target [" << std::to_string(user.id) << "]" << std::endl;
    }



    std::cout << "[Debug] creating embed message" << std::endl;

    uint64_t timestamp = static_cast<uint64_t>(user.get_creation_time());
    std::string created = "<t:" + std::to_string(timestamp) + ">";
    std::string imgURL = user.get_avatar_url(4096, dpp::i_png, true);
    std::cout << "[Debug] img url: " << imgURL << std::endl;


    dpp::embed embed = dpp::embed()
        .set_color(dpp::colors::red_blood)
        .set_title("User Info")

        .set_image(imgURL)
        .set_author(user.global_name, user.get_url(), user.get_default_avatar_url())

        .add_field(
            user.global_name,
            user.get_mention()
        )

        .add_field(
            "User ID",
            std::to_string(user.id)
        )

        .add_field(
            "Account creation",
            created

        )



        .set_footer(
            dpp::embed_footer()
            .set_text("Version: 0.6 [25M7D19]")
            .set_icon("https://cdn.discordapp.com/attachments/1270735248472277004/1370083495313145916/42802-givelove.png?ex=681e3530&is=681ce3b0&hm=dde61ba938af5ce6e8934dfd54b023570c983a1bfdb944d56adcaa2c838d6595&")
        )

        .set_timestamp(time(0));


    dpp::message msg(event.command.channel_id, embed);

    event.reply(msg);
}
