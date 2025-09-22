#include "base_commands.h"

void Commands::command_member_count(dpp::cluster& bot, const dpp::slashcommand_t& event) {



    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    std::cout << "[Debug]: " << "checking parameter value..." << std::endl;

    if (cmd_data.options.empty()) {
        event.reply("pilih subcommandny");
        return;
    }

    auto subcommand = cmd_data.options[0];


    if (subcommand.name == "add") {
        event.thinking();

        std::cout << "[Debug]: " << "add selected" << std::endl;
        /// parameter value getter

        std::string guild_id_str = std::to_string(event.command.guild_id);
        std::string mode = std::get<std::string>(event.get_parameter("mode"));
        std::string channelName;
        short pil = 1;

        if (event.get_parameter("nama_channel").index() != 0) {
            channelName = std::get<std::string>(event.get_parameter("nama_channel")) + " : ";
        } else {
            channelName = mode + " : ";
        }

        if (mode == "members") pil = 1;
        else if (mode == "human") pil = 2;
        else if (mode == "bot") pil = 3;

        /// logic start here
        std::cout << "[DEBUG] member count mode " << mode << "   | channel: " << channelName << " | pil: " << pil<< std::endl;

        /// get the guild member
        bot.guild_get_members(event.command.guild_id, 1000, 0,
        [&bot, event, guild_id_str, pil, channelName](const dpp::confirmation_callback_t& cb) {
            std::cout << "[DEBUG] guild_get_members callback" << std::endl;
            if (cb.is_error()) {
                event.edit_response("error ngab: gagal fetch members");
                std::cout << "error ngab: gagal fetch members" << std::endl;
                return;
            }

            auto members = std::get<dpp::guild_member_map>(cb.value);
            int totalMember = 0;

            if (pil == 1) {
                totalMember = members.size();
            } else if (pil == 2) {
                for (auto& [id, gm] : members) {
                    if (!gm.get_user()->is_bot()) totalMember++;
                }
            } else if (pil == 3) {
                for (auto& [id, gm] : members) {
                    if (gm.get_user()->is_bot()) totalMember++;
                }
            }

            /// create voice channel variable
            dpp::channel voiceChannel;
            voiceChannel.set_name(channelName + std::to_string(totalMember))
                        .set_guild_id(event.command.guild_id)
                        .set_type(dpp::CHANNEL_VOICE);

            /// lock channel permissions
            dpp::permission_overwrite deny_everyone;
            deny_everyone.id = event.command.guild_id;
            deny_everyone.type = dpp::ot_role;
            deny_everyone.deny = dpp::p_view_channel;
            deny_everyone.allow = 0;
            voiceChannel.permission_overwrites.push_back(deny_everyone);



            /// create the voice channel
            bot.channel_create(voiceChannel,
            [event, guild_id_str, pil](const dpp::confirmation_callback_t& cb2) {
                std::cout << "[DEBUG] channel_create callback" << std::endl;
                if (cb2.is_error()) {
                    std::cout << "error ngab: gagal mbuat channel" << std::endl;
                    event.edit_response("error ngab: gagal mbuat channel");
                    return;
                }
                dpp::channel created = std::get<dpp::channel>(cb2.value);

                std::cout << "[Debug]: " << "guild id is: " << guild_id_str << std::endl;
                dpp::snowflake channel_id = created.id;
                std::cout << "[Debug]: async channel id: " << std::to_string(created.id) << std::endl;

                /// edit database
                Config::guildMemberCount(guild_id_str, pil, channel_id);

                /// reply
                event.edit_response("don, cona cek: <#" + std::to_string(created.id) + ">");
            });

        });

        return;


    }
    else if (subcommand.name == "remove") {
        std::cout << "[Debug]: " << "False selected" << std::endl;
        event.reply("[DEBUG] member count dinonaktifkan");
        return;
    }

    event.reply("ha");
}

