#include "base_commands.h"
#include <dpp/dpp.h>

void commands::command_user(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    /// getter sub command option (set, edit, remove)
    //  and global variable for guild config, id etc
    auto subcommand = cmd_data.options[0];

    if (subcommand.name == "info") {
        dpp::user user;

        //event.get
        //if (Config::isLog) std::cout << "[Debug] Entering slash command func" << std::endl;

        auto param = event.get_parameter("user");
        //if (Config::isLog) std::cout << "[Debug] Checking user parameter" << std::endl;

        if (param.index() == 0) {

            user = event.command.usr;
            //if (Config::isLog) std::cout << "Debug: user id: self [" << std::to_string(user.id) << "]" << std::endl;
        } else {
            dpp::snowflake user_id = std::get<dpp::snowflake>(param);
            user = event.command.resolved.users.at(user_id);
            //if (Config::isLog) std::cout << "Debug: user id: target [" << std::to_string(user.id) << "]" << std::endl;
        }



        //if (Config::isLog) std::cout << "[Debug] creating embed message" << std::endl;

        uint64_t timestamp = static_cast<uint64_t>(user.get_creation_time());
        std::string created = "<t:" + std::to_string(timestamp) + "> " + "<t:" + std::to_string(timestamp) + ":R>";
        std::string imgURL = user.get_avatar_url(2048, dpp::i_png, true);
        //if (Config::isLog) std::cout << "[Debug] img url: " << imgURL << std::endl;


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
                .set_text("hihi haha")
                .set_icon("https://cdn.discordapp.com/attachments/1270735248472277004/1370083495313145916/42802-givelove.png?ex=681e3530&is=681ce3b0&hm=dde61ba938af5ce6e8934dfd54b023570c983a1bfdb944d56adcaa2c838d6595&")
            )

            .set_timestamp(time(0));


        dpp::message msg(event.command.channel_id, embed);

        event.reply(msg);
    }

    else if (subcommand.name == "avatar") {
        dpp::user user;

        auto param = event.get_parameter("user");
        //if (Config::isLog) std::cout << "[Debug] Checking user parameter" << std::endl;

        if (param.index() == 0) {

            user = event.command.usr;
            //if (Config::isLog) std::cout << "Debug: user id: self [" << std::to_string(user.id) << "]" << std::endl;
        } else {
            dpp::snowflake user_id = std::get<dpp::snowflake>(param);
            user = event.command.resolved.users.at(user_id);
            //if (Config::isLog) std::cout << "Debug: user id: target [" << std::to_string(user.id) << "]" << std::endl;
        }

        std::string imgURL = user.get_avatar_url(4096, dpp::i_png, true);



        dpp::embed embed = dpp::embed()
            .set_color(dpp::colors::red_blood)
            .set_title("User avatar")

            .set_image(imgURL)

            .set_footer(
                dpp::embed_footer()
                .set_text("hihi haha")
                .set_icon("https://cdn.discordapp.com/attachments/1270735248472277004/1370083495313145916/42802-givelove.png?ex=681e3530&is=681ce3b0&hm=dde61ba938af5ce6e8934dfd54b023570c983a1bfdb944d56adcaa2c838d6595&")
            )

            .set_timestamp(time(0));

        dpp::message msg(event.command.channel_id, embed);

        event.reply(msg);

    }


}
