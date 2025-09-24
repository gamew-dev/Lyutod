/**
 *  InputHandler.cpp
 *
 *  @brief Definition of public functions from the InputHandler class.
 *
 *  This file defines functions to process and assign each input accordingly.
 *
 *  @author Hissats
 */



#include "BotHandler.h"


///ctor
// only assign time value
BotHandler::BotHandler() {
    // assign the bot time start value when creating object
    start = std::time(nullptr);
}


/**
 *  handleMessage
 *
 *  This function take care of message type input and sort them
 *  into their respective type accordingly to create an answer.
 *  See also: Responses.h
 *
 *  @param the bot itself to be able replying
 *  @param message event class that has who sends it, what its content, etc etc
 *
 */
void BotHandler::handleMessage(dpp::cluster& bot, const dpp::message_create_t& event) {

    // Initialize variables for the msg author and it's content
    const dpp::user& tokoh = event.msg.author;
    std::string text = event.msg.content,
                repl;

    // Lowercasing the message
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);


    // i think i should've used else if instead of all if, we'll do that later ^_^
    if (
        text == "halo" || text == "hai"  ||
        text == "woi"  || text == "hi"    )
        {
            repl = Responses::makeMsg("sapa", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }


    if (
        text.find("jawa")  != std::string::npos || text.find("jwa") != std::string::npos  ||
        text.find("jw")    != std::string::npos || text.find("jaua") != std::string::npos )
        {
            bot.message_add_reaction(event.msg.id, event.msg.channel_id, Responses::emoteReact());
            std::clog << "react test" << std::endl;
        }


    // yet another hardcoded experiment
    if (
        text == "test" || text == "tes")
        {
            dpp::message aaa(event.msg.channel_id, "p");

            bot.message_add_reaction(event.msg.id, event.msg.channel_id, Responses::emoteReact());

            aaa.add_component(
                dpp::component().add_component(
                    dpp::component()
                        .set_label("Tes")
                        .set_type(dpp::cot_button)
                        .set_emoji(dpp::unicode_emoji::smile)
                        .set_style(dpp::cos_danger)

                        .set_id("test id")
                )
            );

            event.reply(aaa);
    	}

    if (
        text == "sefi" || text == "sfi"   ||
        text == "sepi" || text == "spi"    )
        {
            repl = Responses::makeMsg("sepi", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    if (
        text == "pagi" || text == "pgi")
        {
            repl = Responses::makeMsg("pagi", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    if (
        text == "siang" || text == "siyang")
        {
            repl = Responses::makeMsg("siang", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    if (
        text == "sore" || text == "sre" || text == "petang")
        {
            repl = Responses::makeMsg("sore", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    if (
        text == "malam" || text == "mlm" || text == "mlam")
        {
            repl = Responses::makeMsg("malam", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    if (
        text == "bobok" || text == "bbok"  || text == "bbk"   ||
        text == "boobk" || text == "obbok" || text == "bobko" ||
        text == "turu"  || text == "turu"  || text == "tr"    ||
        text == "tuur"  || text == "utru"  || text == "bobko"  )
        {
            repl = Responses::makeMsg("bobok", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }

    /// Shutdown command
    //  this one is unique, instead of using slash command Im using this, why? well its cool tho
    //  the function is still experiment and i dont know hos stable it is
    //  usage: shutdown <option>
    //  ex: shutdown now, shutdown 30s, shutdown 5m, other than that it will be treated as default: 60s
    if (text.rfind("$shutdown", 0) == 0) {

        /// Bot owner
        //  only bot owner who has access to it
        //  see also: config.h/cpp
        if (std::to_string(tokoh.id) == Config::botOwner) {

            std::cout << "[Debug]: original input: " << text << std::endl;
            // cut the shutdown string
            std::string arg = text.substr(9);
            std::stringstream ss(arg);
            std::string option;
            ss >> option;
            std::cout << "[Debug]: cutted input: (arg: " << arg << " , option: " << option << ")" << std::endl;

            // set the default value here
            int countdown = 60;

            if (option == "now") {
                countdown = 0;
            }
            else if (!option.empty()) {
                try {

                    char unit = option.back();
                    int value = std::stoi(option.substr(0, option.size()-1));

                    if (unit == 's') {
                        countdown = value;
                    }
                    else if (unit == 'm') {
                        countdown = value * 60;
                    }
                    else {
                        // if there are no timer flag (minutes or second)
                        // then it will be second for default value
                        countdown = std::stoi(option);
                    }
                } catch (...) {
                    // treated as default if all of the option are invalid
                    countdown = 60;
                }
            }

            // a global variabel (static) that... that uh..
            Config::isShutingDown = true;

            // check if there are still active chatbot sessions
            // the last parameter (true) is set to force save the
            // session as soon as the shutdown command given instead
            // of default: 5 minutes
            checkSessions(bot, true);

            bot.message_add_reaction(event.msg.id, event.msg.channel_id, Responses::emoteReact());


            std::string repl;
            if (countdown == 0) repl = "Menonaktifkan bot sekarang...";
            else repl = "Menonaktifkan bot dalam " + std::to_string(countdown) + " detik...";

            bot.message_create(dpp::message(event.msg.channel_id, repl));

            bot.start_timer([&bot](dpp::timer) {
                bot.shutdown();
            }, countdown);

        }

        // of course there are some ppl that would try this
        else {
            repl = Responses::makeMsg("prohibited", tokoh, false);
            bot.message_create(dpp::message(event.msg.channel_id, repl));
        }
    }
}



/**
 *  handleAiRequest
 *
 *  This function manages the chatbot session, input and output and most importanly,
 *  chatGPT API: header, payload, etc.
 *
 *  @param the bot itself to be able replying
 *  @param message event class contain the message/prompt for the ai
 *
 */

void BotHandler::handleAiRequest(dpp::cluster& bot, const dpp::message_create_t& event) {

    /// basic variable
    dpp::snowflake userID64 = event.msg.author.id;
    dpp::snowflake serverID64 = event.msg.guild_id;

    std::string userID = std::to_string(userID64);
    std::string serverID = std::to_string(serverID64);

    dpp::snowflake channel = event.msg.channel_id;

    std::string clearText = Utils::clearMention(event.msg.content, std::to_string(bot.me.id));
    std::string input = "[" + userID +"]: "+ clearText;




    /// Session availability
    //  below is used for checking is the user/server already has an active session or not
    //  the code will create a new Session variable by checking the id and call the readExternal
    //  files function and will create an external files if there was nowhere to be found
    //  (see also: config.h/cpp)
    //
    //  if the id for serverID is 0 that mean it is a DM
    //  though there's a possibility that the id of an user and a server is same, or not.. idk
    //  anywayy... what are the chances right??? ^_^

    if (ServerSessions.find(serverID64) != ServerSessions.end()) {
        std::cout << "server sudah memiliki session" << std::endl;
    } else {
        if (serverID64 == 0) {
            serverID64 = userID64;
            serverID = std::to_string(serverID64);
        }

        event.reply("`# Sesi Chat dimulai, sesi akan berakhir setelah > 10 menit tidak ada pesan baru");

        auto memoryRead = Config::serverReadMemory(serverID);
        BotHandler::ServerSessions[serverID64] = ServerSessionStruct{memoryRead, std::chrono::steady_clock::now()};

    }

    if (UserSessions.find(userID64) != UserSessions.end()) {
        std::cout << "User sudah ada!\n";
    } else {
        std::string memoryRead = Config::userReadMemory(userID);
        BotHandler::UserSessions[userID64] = UserSessionStruct{memoryRead, std::chrono::steady_clock::now()};
    }

    std::cout << "[Debug] prompt is: " << input << std::endl;


    /// Ai prompt
    //  the brainwasing spell magic
    std::string prompt =
    "Aturan dan Gaya ngobrol: santai, singkat, jelas, gak usah trlalu formal. "
    "Boleh campur bahasa sehari2 biar lebih manusiawi. ushakan jwb pendek, jngan monoton. "
    "Selalu cek Memory sbelum mmbuat jawaban, apakah user memiliki custom prompt/ jawaban dan konteks ada di memory"
    "Jangan jawab datar dengan ”saya adalah chatbot/asisten”, lu itu temen ngobrol biasa. "
    "Jawablah secara alami, ekspresif, dan singkat, seolah-olah kamu manusia yang sedang berbincang, bukan asisten."
    "Hindari pnutup formal kayak ”semoga membantu” atau ”apakah ada hal lain”. "
    "Fokus ke isi obrolan, jangan jelasin teknis panjang lebar kecuali diminta. "
    "Kalau ada hal sepele, jawab sepele juga, boleh bercanda dikit. ikuti perkembangan jaman juga, gunakan emot nangis buat ketawa"
    "Saya bakal kasih memory tentang user dan histori obrolan (kadang kosong). "
    "Jawablah dalam format JSON dengan dua field: {”output”: ”jawaban untuk user”, ”memory”: ”catatan penting atau jika tidak ada berikan '-'”}"
    "Contoh:"
    "[user]: Saya suka apel"
    "[anda]: {”output”: ”ohh suka apel toh” (atau) ”ywdh sih”, ”memory”: ”suka apel”}"
    "[user]: Halo"
    "[anda]: {”output”: ”halo bro” (atau) ”iyaa”, ”memory”: ”-”}"
    "[user]: Saya suka pisang dan jeruk [MEMORY: suka apel]"
    "[anda]: {”output”: ”emang enak sih”, ”memory”: ”suka pisang, jeruk”}";


    /// History & Memory fetch
    //  call the session with the given id and store it.
    //  the user memory usage is as simple as concantenate it
    //  while the history vector would need a bit of looping
    //  for make it a good use
    auto& session = UserSessions[userID64];
    std::string memory = session.memory;
    std::cout << "[Debug] memory is: " << memory << std::endl;

    auto& server = ServerSessions[serverID64];
    std::vector<std::string> history = server.history;


    /// JSON payload for the API request.
    //  contains message info, chat history, prompt, and user memory.
    //  this will be merged into the main payload later and send to
    //  the API Request (see variable below).
    nlohmann::json messagesPayload = nlohmann::json::array();

    // ai prompt and user memory
    messagesPayload.push_back({
        {"role", "system"},
        {"content", prompt + "\n\n[MEMORY]\n" + memory}
    });

    // chat history
    for (const auto& line : history) {
        std::cout<< "reading history: " << line << std::endl;
        if (line.rfind("[anda]:", 0) == 0) {

            messagesPayload.push_back({
                {"role", "assistant"},
                {"content", line}
            });
        }
        else {
            messagesPayload.push_back({
                {"role", "user"},
                {"content", line}
            });
        }

    }


    // user input
    messagesPayload.push_back({
        {"role", "user"},
        {"content", input}
    });


    /// Json Payload variable
    //  here it is, the payload variable that what we gonna send to the API
    //  in here it contains the model of the ai that we are using, messages
    //  from the logic above, and a response format
    nlohmann::json payload = {
        {"model", "gpt-4o-mini"},
        {"messages", messagesPayload},
        {"response_format", {
            {"type", "json_object"}
        }}
    };

    /// convert json payload into string
    std::string postdata = payload.dump();


    /// Request headers
    std::string auth = "Bearer " + Config::gptToken;
    dpp::http_headers headers;
    headers.emplace("Authorization", auth);

    /// History
    //  push the user input/question into the history vector
    //  since we already used it in above has no purpose now
    //  might aswell save it now
    server.history.push_back(input);


    /// Request
    //  here it will do the thing, that and something
    bot.request(
        "https://api.openai.com/v1/chat/completions",
        dpp::m_post,
        [&](const dpp::http_request_completion_t& cc) {
            std::cout << "Done requesting with status:" << std::to_string(cc.status) << std::endl;
            if (cc.status == 200) {
                try {
                    /// Success
                    //  if the callback completion status is 200 or success
                    //  we got the ai answer. however, the content is still in
                    //  json form and we still need to parse it
                    auto j = nlohmann::json::parse(cc.body);

                    /// Parsing
                    //  string content has the value of the ai message output, but...
                    //  in the brainwashing prompt above, we ask the output to be formated in json
                    //  "{output: chat, memory: -}", therefore we need to parse it again
                    //  while the int token, well.. hold the token usage value
                    std::string content = j["choices"][0]["message"]["content"];
                    int inputToken = j["usage"]["prompt_tokens"].get<int>();
                    int outputToken = j["usage"]["completion_tokens"].get<int>();

                    // parse the string content
                    nlohmann::json content_json = nlohmann::json::parse(content);
                    std::string answer = content_json["output"];
                    std::string memoOut = content_json["memory"];
                    std::cout << "memory out is: <" << memoOut << ">"<<std::endl;

                    /// Reply
                    //  now, since we got the answer that we wanted, we can reply the original
                    //  chat with this event.reply()
                    event.reply(answer);

                    /// Session update
                    //  update the user and server session, we use auto& to automaticly change
                    //  the original value.
                    //  most of the logic below this are self explanatory
                    auto& session = UserSessions[userID64];
                    session.last_activity = std::chrono::steady_clock::now();

                    if (memoOut != "-") {
                        if (session.memory == "") {
                            session.memory = memoOut;
                        }
                        else {
                            std::cout << "updating " << userID <<" memory: " << memoOut << std::endl;
                            session.memory += ", " + memoOut;
                        }
                    }

                    auto& server = ServerSessions[serverID64];
                    server.last_activity = std::chrono::steady_clock::now();
                    server.lastChannel = channel;
                    server.inputUsage += inputToken;
                    server.outputUsage += outputToken;

                    server.history.push_back("[anda]: " + answer);

                    /// Todo: change into config for better control
                    //  well, its a max size of history that we gonna send
                    if (server.history.size() >= 5) {
                        server.history.erase(server.history.begin());
                    }

                } catch (...) {
                    bot.message_create(dpp::message(event.msg.channel_id, "woe error: parsing"));
                }
            } else {
                std::cout << "Error: " << cc.body << "\n";
                bot.message_create(dpp::message(event.msg.channel_id, "<@465096085224947722>, status: " + std::to_string(cc.status)));
            }
        },
        postdata,
        "application/json",
        headers

    );




}

/**
 *  handleSlash
 *
 *  It just a wrapper, throw it again into command file
 *  See also: Base_commands.h
 *
 *  @param the bot itself to be able replying
 *  @param slashcommand event class
 *
 */

void BotHandler::handleSlash(dpp::cluster& bot, const dpp::slashcommand_t& event) {

    std::string command = event.command.get_command_name();

    std::cout << "[LOG] Menerima command: " << command << std::endl;

    if (command == "status") {
        Commands::command_status(start, bot, event);
    }

    else if (command == "server_info") {
        Commands::command_server_info(bot, event);
    }

    else if (command == "say") {
        Commands::command_say(bot, event);
    }

    else if (command == "set_autorole") {
        std::cout << "[DEBUG] Selecting autorole" << std::endl;
        Commands::command_set_autorole(bot, event);
    }

    else if (command == "user_info") {
        std::cout << "[DEBUG] Entry user info" << std::endl;
        Commands::command_user_info(bot, event);
    }
    else if (command == "set_member_count") {
        std::cout << "[DEBUG] Memanggil fungsi sensus" << std::endl;
        Commands::command_member_count(bot, event);
    }
    else if (command == "sync_guild") {
        Commands::command_sync_guild(bot, event);
    }

}

/**
 *  handleButtonEvent
 *
 *  Currrently just testing and hardcoded for test chat
 *
 *  @param the bot itself
 *  @param button click event class
 *
 */

void BotHandler::handleButtonEvent(dpp::cluster& bot, const dpp::button_click_t& event) {

    if (std::to_string(event.command.usr.id) == Config::botOwner) {
        event.reply(dpp::ir_update_message, "Tos <:owo:1370082279006666802>");
    } else {
        std::string repl = Responses::makeMsg("prohibited", event.command.usr, false);
        event.reply(dpp::ir_update_message, repl);
    }


}

/**
 *  handleGuildNewMem
 *
 *  Manage new user that joined, currently paired with
 *  autoRole command and greet chat
 *
 *  @param the bot itself to be able replying and assign role
 *  @param guild member add event class
 *
 */

void BotHandler::handleGuildNewMem(dpp::cluster& bot, const dpp::guild_member_add_t& event) {

    /// Basic variable
    const dpp::user& tokoh = *(event.added.get_user());
    const dpp::snowflake server = event.added.guild_id;

    /// Greet
    //  honestly, there are other way to get the guild/server using
    //  event.adding_guild, idk why i didn't used it in the first time
    //  probably leftover when experimenting, but hey... it work tho
    bot.guild_get(server, [&bot, &tokoh](const dpp::confirmation_callback_t& cb) {
        if (!cb.is_error()) {
            auto g = std::get<dpp::guild>(cb.value);
            bot.message_create(dpp::message(g.system_channel_id, Responses::makeMsg("sambut", tokoh, false)));

        }
    });

    /// Get guild config
    //  is the guild using autorole?
    auto guildConfig = Config::guildLoadConfig(std::to_string(static_cast<uint64_t>(server)));

    std::cout << "[LOG]New member in server: " << guildConfig.name << std::endl;

    if (guildConfig.autoRoleEnabled) {
        bot.guild_member_add_role(server, tokoh.id, guildConfig.autoRoleID, [&guildConfig](const dpp::confirmation_callback_t& callback) {
            if (callback.is_error()) {
                std::cerr << "\e[0;31m"<<"[ERR]" << "\e[0m"<< " Can't given the role: " << callback.get_error().message << "\n";
            } else {
                std::cout << "[LOG] Successfully given the role: " << guildConfig.autoRoleName << std::endl;
            }
        });

    }

    /// @TODO: add an automatic cencus for ...
    bot.guild_get_members(server, 1000, 0,
        [&bot, event, guildConfig](const dpp::confirmation_callback_t& cb) {
            std::cout << "[DEBUG] guild_get_members callback" << std::endl;

            if (cb.is_error()) {
                //event.edit_response("eror ngab: " + cb.get_error().message);
                return;
            }
            else {
                //event.edit_response("sinkronisasi...");

                auto members = std::get<dpp::guild_member_map>(cb.value);
                int totalMember = 0;
                int botMember = 0;
                int humanMember = 0;

                totalMember = members.size();
                for (auto& [id, gm] : members) {
                    if (gm.get_user()->is_bot()) botMember++;
                }
                humanMember = totalMember - botMember;



                if (guildConfig.memberCountChannel1 == 0) {
                    std::cout << "[Debug]: all member skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel1, [&bot, event, totalMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(totalMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: all member error..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk all member: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: all member updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get all channel" << std::endl;}
                    });
                }

                if (guildConfig.memberCountChannel2 == 0) {
                    std::cout << "[Debug]: human only skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel2, [&bot, event, humanMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(humanMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: human only error..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk member only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: human only updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get human channel" << std::endl;}
                    });
                }

                if (guildConfig.memberCountChannel3 == 0) {
                    std::cout << "[Debug]: bot only skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel3, [&bot, event, botMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(botMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: bot only fail..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk bot only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: bot only updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get bot channel" << std::endl;}
                    });
                }
            }
        });


    /// end here
}


void BotHandler::handleGuildRemMem(dpp::cluster& bot, const dpp::guild_member_remove_t& event) {

    const dpp::snowflake server = event.removing_guild.id;

    auto guildConfig = Config::guildLoadConfig(std::to_string(static_cast<uint64_t>(server)));

    bot.guild_get_members(server, 1000, 0,
        [&bot, event, guildConfig](const dpp::confirmation_callback_t& cb) {
            std::cout << "[DEBUG] guild_get_members callback" << std::endl;

            if (cb.is_error()) {
                //event.edit_response("eror ngab: " + cb.get_error().message);
                return;
            }
            else {
                //event.edit_response("sinkronisasi...");

                auto members = std::get<dpp::guild_member_map>(cb.value);
                int totalMember = 0;
                int botMember = 0;
                int humanMember = 0;

                totalMember = members.size();
                for (auto& [id, gm] : members) {
                    if (gm.get_user()->is_bot()) botMember++;
                }
                humanMember = totalMember - botMember;



                if (guildConfig.memberCountChannel1 == 0) {
                    std::cout << "[Debug]: all member skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel1, [&bot, event, totalMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(totalMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: all member error..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk all member: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: all member updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get all channel" << std::endl;}
                    });
                }

                if (guildConfig.memberCountChannel2 == 0) {
                    std::cout << "[Debug]: human only skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel2, [&bot, event, humanMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(humanMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: human only error..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk member only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: human only updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get human channel" << std::endl;}
                    });
                }

                if (guildConfig.memberCountChannel3 == 0) {
                    std::cout << "[Debug]: bot only skipped" << std::endl;

                }
                else {
                    bot.channel_get(guildConfig.memberCountChannel3, [&bot, event, botMember](const dpp::confirmation_callback_t& cc) {
                        if (!cc.is_error()) {

                            dpp::channel ch = std::get<dpp::channel>(cc.value);
                            std::string base = ch.name.substr(0, ch.name.find(" : "));
                            std::string newName = base + " : " + std::to_string(botMember);

                            ch.set_name(newName);

                            bot.channel_edit(ch, [&bot, &event, ch](const dpp::confirmation_callback_t& cc2) {
                                if (cc2.is_error()) {
                                    std::cout << "[Debug]: bot only fail..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> error untuk bot only: " + cc2.get_error().message));

                                } else {
                                    std::cout << "[Debug]: bot only updated..." << std::endl;
                                    //bot.message_create(dpp::message(event.command.channel_id, "<#"+ std::to_string(ch.id) +"> terupdate"));

                                }

                            });
                        } else {std::cout << "[Debug]: Error get bot channel" << std::endl;}
                    });
                }
            }
        });
}


/**
 *  updatePresence
 *
 *  presence setting, randomly select one from Presence vector
 *  see also: BotHandler.h
 *
 *  @param the bot itself
 *
 */

void BotHandler::updatePresence(dpp::cluster& bot) {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, presence.size() - 1);

    bot.set_presence(presence[dist(gen)]);
    std::cout << "[LOG] Updating presence status..." << std::endl;
}


/**
TESTING ONLY, HARDCODED COMMAND
*/
void BotHandler::preRegSlash(dpp::cluster& bot) {

    for (auto& [key, cmd] : Commands::commands_list) {
        if (key == "6") {
            bot.guild_command_create(cmd, 1270735247922692177, [](const dpp::confirmation_callback_t& cb) {
            if (cb.is_error()) {
                std::cerr << "Gagal register command: " << cb.get_error().message << "\n";
            } else {
                std::cout << "Command diregister!\n";
            }
            sleep(3);
            });
        }

    }

}

void BotHandler::preDelSlash(dpp::cluster& bot) {
    bot.guild_bulk_command_delete(1349036976627777557);
    //bot.guild_command_
}

/**
 *  checkSessions
 *
 *  checking the chatbot session every 5 minutes (since bot online), for every
 *  session that has "last time chatted" more that 5 minutes would be closed and
 *  saved externally
 *  see also: Config.h/cpp
 *
 *  @param the bot itself
 *  @param is forced to stop boolean value
 *
 */

void BotHandler::checkSessions(dpp::cluster& bot, const bool& forced) {
    /// Time getter
    auto now = std::chrono::steady_clock::now();

    /// Checking every user that has an active session
    //  there are 2 modes for closing session, which is normal and forced
    //  both are controled using the forced parameter
    //
    //  normal: sessions are written externally and cleared from memory
    //  forced: (e.g., on shutdown) sessions are saved but not cleared,
    //  but new messages are no longer recorded.
    for (auto it = UserSessions.begin(); it != UserSessions.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_activity);
        if (elapsed.count() >= 5 || forced) {
            std::cout << "Sesi berakhir untuk: " << it->first << std::endl;
            std::string id = std::to_string(it->first);
            std::string memory = it->second.memory;
            std::cout << "memori akhir: " << memory << std::endl;

            Config::userUpdateMemory(id, memory);

            if (!Config::isShutingDown) {
                it = UserSessions.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }

    /// Server session
    //  same with user session but with more variable logic
    for (auto it = ServerSessions.begin(); it != ServerSessions.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_activity);
        if (elapsed.count() >= 5 || forced) {

            std::cout << "Last channel: " << it->second.lastChannel << std::endl;

            std::string inputToken = std::to_string(it->second.inputUsage),
                        outputToken = std::to_string(it->second.outputUsage),
                        totalToken = std::to_string(it->second.inputUsage + it->second.outputUsage);

            std::string closing = (forced) ? "Sesi diakhiri untuk saat ini, anda masih bisa melanjutkan percakapan tetapi tidak akan tersimpan" : "sesi telah berakhir untuk membebaskan memory, anda bisa memulainya lagi kapan saja";
            std::string repl =  closing + "\n"
                               "token usage: " + inputToken + " : " + outputToken + " : " + totalToken;

            /// Announce the closing
            bot.message_create(dpp::message(it->second.lastChannel, repl));

            std::cout << "Sesi berakhir untuk server: " << it->first << std::endl;
            std::string id = std::to_string(it->first);
            std::vector<std::string> history = it->second.history;

            Config::serverUpdateHistory(id, history);

            if (!Config::isShutingDown) {
                it = ServerSessions.erase(it);
            } else {
                ++it;
            }
        } else {
            ++it;
        }
    }
}
