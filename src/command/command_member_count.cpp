#include "base_commands.h"

void Commands::command_member_count(dpp::cluster& bot, const dpp::slashcommand_t& event) {


    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    std::cout << "[Debug]: " << "checking parameter value..." << std::endl;
    auto subcommand = cmd_data.options[0];


    if (subcommand.name == "add") {
        event.thinking();
        std::cout << "[Debug]: " << "add selected" << std::endl;
        /// parameter value getter


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
        bot.guild_get_members(event.command.guild_id, 1000, 0, [&](const dpp::confirmation_callback_t& cb) {
            if (cb.is_error()) {
                event.edit_response("error ngab: gagal fetch members");
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
            bot.channel_create(voiceChannel, [&](const dpp::confirmation_callback_t& cb2) {
                if (cb2.is_error()) {
                    event.edit_response("error ngab: gagal mbuat channel");
                    return;
                }
                dpp::channel created = std::get<dpp::channel>(cb2.value);
                std::string guild_id = std::to_string(event.command.guild_id);
                std::cout << "[Debug]: " << "guild id is: " << guild_id << std::endl;
                dpp::snowflake channel_id = created.id;
                std::cout << "[Debug]: async channel id: " << std::to_string(created.id) << std::endl;

                /// edit database
                Config::guildMemberCount(guild_id, pil, channel_id);
                event.edit_response("don, cona cek: <#" + std::to_string(created.id) + ">");
            });
            //std::cout << "[Debug]: channel id: " << std::to_string(channel_id) << std::endl;
            //event.reply("k");
        });

        //event.reply("[DEBUG] member count diaktifkan dengan mode " + mode + " dan channel: " + channelName);


    }
    else if (subcommand.name == "remove") {
        std::cout << "[Debug]: " << "False selected" << std::endl;
        event.reply("[DEBUG] member count dinonaktifkan");
    }
}

