#include "base_commands.h"

void Commands::command_member_count(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    event.thinking();

    /// Sub command option getter or.. the data and else blablablablablbalba
    //  sorry..
    dpp::command_interaction cmd_data = event.command.get_command_interaction();

    /// global variable for this slashcmmand
    std::string guild_id_str = std::to_string(event.command.guild_id);

    /// Check
    if (cmd_data.options.empty()) {
        event.edit_response("pilih subcommandny");
        return;
    }

    /// getter sub command option (add, remove, edit, sync)
    auto subcommand = cmd_data.options[0];


    if (subcommand.name == "add") {
        ///


        std::cout << "[Debug]: " << "add selected" << std::endl;

        /// parameter value getter
        std::string mode = std::get<std::string>(event.get_parameter("mode"));
        std::string channelName;

        /// Guild config
        auto data = Config::guildLoadConfig(guild_id_str);


        short pil = 1;

        if (event.get_parameter("nama_channel").index() != 0) {
            channelName = std::get<std::string>(event.get_parameter("nama_channel")) + " : ";
        } else {
            channelName = mode + " : ";
        }

        if (mode == "members") {
            if (data.memberCountChannel1 != 0) {
                event.edit_response("channel all member dh ada: <#" + std::to_string(data.memberCountChannel1) + ">");
                return;
            }
            pil = 1;
        }
        else if (mode == "human") {
            if (data.memberCountChannel2 != 0) {
                event.edit_response("channel member only dh ada: <#" + std::to_string(data.memberCountChannel2) + ">");
                return;
            }
            pil = 2;
        }
        else if (mode == "bot") {
            if (data.memberCountChannel3 != 0) {
                event.edit_response("channel bot only dh ada: <#" + std::to_string(data.memberCountChannel3) + ">");
                return;
            }
            pil = 3;
        } else {
            event.edit_response("eror ngab: mode invalid... how bruh");
            return;
        }


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
        std::string mode = std::get<std::string>(event.get_parameter("mode"));

        auto data = Config::guildLoadConfig(guild_id_str);
        dpp::snowflake channel_id;

        if (mode == "members") {
            channel_id = data.memberCountChannel1;
            Config::guildMemberCount(guild_id_str, 4, 0);
        }
        else if (mode == "human") {
            channel_id = data.memberCountChannel2;
            Config::guildMemberCount(guild_id_str, 5, 0);
        }
        else if (mode == "bot") {
            channel_id = data.memberCountChannel3;
            Config::guildMemberCount(guild_id_str, 6, 0);
        } else {
            event.edit_response("eror ngab: mode invalid... how bruh");
            return;
        }

        if (channel_id == 0) {
            event.edit_response("bilek");
            return;
        }

        event.edit_response("menghapus channel " + mode +"...");

        bot.channel_delete(channel_id, [&bot,&event, mode](const dpp::confirmation_callback_t& cb) {
            std::cout << "[DEBUG] callbackdhannel delete..." << std::endl;
            if (cb.is_error()) {
                bot.message_create(dpp::message(event.command.channel_id, "eror ngab: gbisa apus channel [" + mode + "]: " + cb.get_error().message));
                //event.edit_response("eror ngab: gbisa apus channel [" + mode + "]: " + cb.get_error().message);
            } else {

                bot.message_create(dpp::message(event.command.channel_id, "don, channel [" + mode + "] dh dihapus"));
                //event.edit_response("don, channel [" + mode + "] dh dihapus");
            }
        });
        return;
    }

    else if (subcommand.name == "edit") {
        std::cout << "[Debug]: " << "False selected" << std::endl;

        std::string newName = std::get<std::string>(event.get_parameter("nama"));
        std::string mode = std::get<std::string>(event.get_parameter("mode"));
        dpp::snowflake channel_id;

        auto data = Config::guildLoadConfig(guild_id_str);

        if (mode == "members" && data.memberCountChannel1 != 0) {
            channel_id = data.memberCountChannel1;
        }
        else if (mode == "human" && data.memberCountChannel2 != 0) {
            channel_id = data.memberCountChannel2;
        }
        else if (mode == "bot" && data.memberCountChannel3 != 0) {
            channel_id = data.memberCountChannel3;
        }
        else {
            event.edit_response("bilek");
            return;
        }

        event.edit_response("ngedit channel [" + mode + "]...");



        bot.channel_get(channel_id, [&bot, event, newName](const dpp::confirmation_callback_t& cb) {
            if (cb.is_error()) {
                event.edit_response("eror ngab: " + cb.get_error().message);
                return;
            }

            dpp::channel ch = std::get<dpp::channel>(cb.value);

            std::string oldName = ch.name;
            size_t pos = oldName.find(" : ");
            std::string numbers;

            if (pos != std::string::npos) {
                numbers = oldName.substr(pos + 3);
            } else {
                numbers = "0 wooo eror";
            }

            ch.set_name(newName + " : " + numbers);

            bot.channel_edit(ch, [&event, newName, ch](const dpp::confirmation_callback_t& cb2) {
                if (cb2.is_error()) {
                    event.edit_response("eror ngab: " + cb2.get_error().message);
                } else {
                    event.edit_response("don, cona cek <#" + std::to_string(ch.id) + ">");
                }
            });
        });
    }

    else if (subcommand.name == "sync") {

        auto data = Config::guildLoadConfig(guild_id_str);


        bot.guild_get_members(event.command.guild_id, 1000, 0,
        [&bot, event, data](const dpp::confirmation_callback_t& cb) {
            std::cout << "[DEBUG] guild_get_members callback" << std::endl;

            if (cb.is_error()) {
                event.edit_response("eror ngab: " + cb.get_error().message);
                return;
            }
            else {
                event.edit_response("sinkronisasi...");

                auto members = std::get<dpp::guild_member_map>(cb.value);
                int totalMember = 0;
                int botMember = 0;
                int humanMember = 0;

                totalMember = members.size();
                for (auto& [id, gm] : members) {
                    if (gm.get_user()->is_bot()) botMember++;
                }
                humanMember = totalMember - botMember;



                if (data.memberCountChannel1 == 0) {
                    std::cout << "[Debug]: all member skipped" << std::endl;

                }
                else {
                    bot.channel_get(data.memberCountChannel1, [&bot, event, totalMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(totalMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: all member error..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk all member: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: all member updated..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get all channel" << std::endl;}
                    });
                }

                if (data.memberCountChannel2 == 0) {
                    std::cout << "[Debug]: human only skipped" << std::endl;

                }
                else {
                    bot.channel_get(data.memberCountChannel2, [&bot, event, humanMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(humanMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: human only error..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk member only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: human only updated..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get human channel" << std::endl;}
                    });
                }

                if (data.memberCountChannel3 == 0) {
                    std::cout << "[Debug]: bot only skipped" << std::endl;

                }
                else {
                    bot.channel_get(data.memberCountChannel3, [&bot, event, botMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(botMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: bot only fail..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk bot only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: bot only updated..." << std::endl;
                                    bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get bot channel" << std::endl;}
                    });
                }

                //event.edit_response("finishing sinkronisasi...");
                std::cout << "[Debug]: Starting timer..." << std::endl;
                bot.start_timer([&bot, &event](dpp::timer h) {
                    std::cout << "[Debug]: done: "  << std::endl;

                    event.edit_response("sinkronisasi selesai");
                    bot.stop_timer(h);

                }, 10);
            }
        });
        return;
    }

    event.reply("ha");
}

