#include "BotHandler.h"


//ctor
BotHandler::BotHandler() {
    // assign the bot time start value when creating object
    start = std::time(nullptr);
    Config::clientLoadConfig();
}




void BotHandler::handleMessage(dpp::cluster& bot, const dpp::message_create_t& event) {

    // Initialize variables for the msg author and it's content
    const dpp::user& tokoh = event.msg.author;
    std::string text = event.msg.content,
                repl;

    // Lowercasing the message
    std::transform(text.begin(), text.end(), text.begin(), ::tolower);

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


    if (
        text == "test" || text == "tes")
        {
            dpp::message aaa(event.msg.channel_id, "p");

            //aaa.set_allowed_mentions(true, true, true, true);
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

            /* Reply to the user with our message. */
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

    if (
        text == "shutdown" || text == "turn off")
        {
            if (std::to_string(tokoh.id) == Config::botOwner) {
                checkSessions();

                bot.message_add_reaction(event.msg.id, event.msg.channel_id, Responses::emoteReact());

                std::string repl = "Menonaktifkan bot dalam 5 detik...";
                bot.message_create(dpp::message(event.msg.channel_id, repl));

                bot.start_timer([&bot](dpp::timer) {
                    bot.shutdown();
                }, 5);

            }
            else {
                repl = Responses::makeMsg("prohibited", tokoh, false);
                bot.message_create(dpp::message(event.msg.channel_id, repl));

            }

    	}


}

void BotHandler::handleAiRequest(dpp::cluster& bot, const dpp::message_create_t& event) {

    dpp::snowflake userID64 = event.msg.author.id;
    dpp::snowflake serverID64 = event.msg.guild_id;
    std::string userID = std::to_string(userID64);
    std::string serverID = std::to_string(serverID64);
    std::string clearText = Utils::clearMention(event.msg.content, std::to_string(bot.me.id));
    std::string input = "[" + userID +"]: "+ clearText;

    std::cout << "get server id: " << serverID << std::endl;

    if (ServerSessions.find(serverID64) != ServerSessions.end()) {
        std::cout << "server sudah memiliki session" << std::endl;
    } else {
        if (serverID64 == 0) {
            serverID64 = userID64; // berarti DM
            serverID = std::to_string(serverID64);
        }

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


    std::string prompt =
    "Aturan gaya: usahakan jawab singkat, jelas, tidak bertele-tele, dan tolak permintaan yang terlalu panjang atau teknis."
    "Jika ditanya mengenai identitas Anda, usahakan jangan menjawab dengan datar ”saya adalah chatbot/asisten virtual/dsb...”"
    "Jangan menambahkan pertanyaan balik atau ajakan tambahan di akhir jawaban, kecuali diminta secara eksplisit."
    "Hindari penutup bernuansa formal atau pelayanan seperti “apakah ada hal lain...”, “semoga membantu...”, atau “saya di sini untuk...”."
    "Jawablah secara alami, ekspresif, dan singkat, seolah-olah kamu manusia yang sedang berbincang, bukan asisten."
    "Fokus pada isi percakapan, jangan memanjangkan topik secara teknis atau mendalam kecuali diminta."
    "Saya akan memberi anda memory mengenai user dan histori percakapan yang sedang berbincang kepada anda saat ini (memory bisa saja kosong):"
    "Jawablah dalam format JSON dengan dua field: {”output”: ”jawaban untuk user”, ”memory”: ”catatan penting atau jika tidak ada berikan '-'”}"
    "Contoh:"
    "[user]: Saya suka apel"
    "[anda]: {”output”: ”... (bebas anda)”, ”memory”: ”suka apel”}"
    "[user]: Halo"
    "[anda]: {”output”: ”... (bebas anda)”, ”memory”: ”-”}"
    "[user]: Saya suka pisang dan jeruk [MEMORY: suka apel]"
    "[anda]: {”output”: ”... (bebas anda)”, ”memory”: ”suka pisang, jeruk”}"
    ;


    auto& session = UserSessions[userID64];
    std::string memory = session.memory;
    std::cout << "[Debug] memory is: " << memory << std::endl;

    auto& server = ServerSessions[serverID64];
    std::vector<std::string> history = server.history;

    nlohmann::json messagesPayload = nlohmann::json::array();

    // ai prompt and user memory
    messagesPayload.push_back({
        {"role", "system"},
        {"content", prompt + "\n\n[MEMORY]\n" + memory}
    });

    // history
    for (const auto& line : history) {
        std::cout<< "reading history: " << line << std::endl;
        if (line.rfind("[anda]:", 0) == 0) {
            // kalau prefix "[anda]:"
            //std::string content = line.substr(7); // buang "[anda]: "
            messagesPayload.push_back({
                {"role", "assistant"},
                {"content", line}
            });
        }
        else {
            // kalau prefix "[user]:"
            //std::string content = line.substr(7); // buang "[user]: "
            messagesPayload.push_back({
                {"role", "user"},
                {"content", line}
            });
        }
        // kalau nanti ada format lain bisa ditambah else if
    }


    // user input
    messagesPayload.push_back({
        {"role", "user"},
        {"content", input}
    });

    nlohmann::json payload = {
        {"model", "gpt-4o-mini"},
        {"messages", messagesPayload},
        {"response_format", {
            {"type", "json_object"}
        }}

    };
    std::string postdata = payload.dump();
    //std::cout << "[Debug] Final Payload: " << postdata << std::endl;


    std::string auth = "Bearer " + Config::gptToken;

    dpp::http_headers headers;
    headers.emplace("Authorization", auth);

    std::string answerButDifferentScopingIDKBruh;
    server.history.push_back(input);

    bot.request(
        "https://api.openai.com/v1/chat/completions",
        dpp::m_post,
        [&](const dpp::http_request_completion_t& cc) {
            std::cout << "Done requesting with status:" << std::to_string(cc.status) << std::endl;
            if (cc.status == 200) {
                try {

                    auto j = nlohmann::json::parse(cc.body);

                    std::string content = j["choices"][0]["message"]["content"];

                    nlohmann::json content_json = nlohmann::json::parse(content);

                    std::string answer = content_json["output"];
                    std::string memoOut = content_json["memory"];
                    std::cout << "memory out is: <" << memoOut << ">"<<std::endl;

                    event.reply(answer);
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

                    server.history.push_back("[anda]: " + answer);


                    if (server.history.size() >= 5) {
                        server.history.erase(server.history.begin()); // hapus paling lama
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

}


void BotHandler::handleButtonEvent(dpp::cluster& bot, const dpp::button_click_t& event) {

    if (std::to_string(event.command.usr.id) == Config::botOwner) {
        event.reply(dpp::ir_update_message, "Tos <:owo:1370082279006666802>");
    } else {
        std::string repl = Responses::makeMsg("prohibited", event.command.usr, false);
        event.reply(dpp::ir_update_message, repl);
    }


}


void BotHandler::handleGuildNewMem(dpp::cluster& bot, const dpp::guild_member_add_t& event) {

    const dpp::user& tokoh = *(event.added.get_user());
    const dpp::snowflake server = event.added.guild_id;

    bot.guild_get(server, [&bot, &tokoh](const dpp::confirmation_callback_t& cb) {
        if (!cb.is_error()) {
            auto g = std::get<dpp::guild>(cb.value);
            bot.message_create(dpp::message(g.system_channel_id, Responses::makeMsg("sambut", tokoh, false)));

        }
    });

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
}


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
        bot.guild_command_create(cmd, 1349036976627777557, [](const dpp::confirmation_callback_t& cb) {
            if (cb.is_error()) {
                std::cerr << "Gagal register command: " << cb.get_error().message << "\n";
            } else {
                std::cout << "Command diregister!\n";
            }
            sleep(1);
        });
    }
}

void BotHandler::preDelSlash(dpp::cluster& bot) {
    bot.guild_bulk_command_delete(1270735247922692177);
}








//private

void BotHandler::checkSessions() {
    auto now = std::chrono::steady_clock::now();
    for (auto it = UserSessions.begin(); it != UserSessions.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_activity);
        if (elapsed.count() >= 5) {
            std::cout << "Sesi berakhir untuk: " << it->first << std::endl;
            std::string id = std::to_string(it->first);
            std::string memory = it->second.memory;
            std::cout << "memori akhir: " << memory << std::endl;

            Config::userUpdateMemory(id, memory);

            it = UserSessions.erase(it); // hapus session
        } else {
            ++it;
        }
    }

    for (auto it = ServerSessions.begin(); it != ServerSessions.end(); ) {
        auto elapsed = std::chrono::duration_cast<std::chrono::minutes>(now - it->second.last_activity);
        if (elapsed.count() >= 5) {
            std::cout << "Sesi berakhir untuk server: " << it->first << std::endl;
            std::string id = std::to_string(it->first);
            std::vector<std::string> history = it->second.history;
            //std::cout << "memori akhir: " << memory << std::endl;

            Config::serverUpdateHistory(id, history);

            it = ServerSessions.erase(it); // hapus session
        } else {
            ++it;
        }
    }
}
