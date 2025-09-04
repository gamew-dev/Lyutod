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
                dpp::message aaa(event.msg.channel_id, "<:turu:1370067202635595817>");

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



    if (Sessions.find(event.msg.author.id) != Sessions.end()) {
        std::cout << "User sudah ada!\n";
    } else {
        BotHandler::Sessions[event.msg.author.id] = UserSession{"", std::chrono::steady_clock::now()};
    }

    std::string input = std::to_string(event.msg.author.id) +": "+ Utils::clearMention(event.msg.content, std::to_string(bot.me.id));
    std::cout << "[Debug] prompt is: " << input << std::endl;


    std::string prompt =
    "Kamu adalah Lyudya (Lyu-chan), chatbot Discord yang diciptakan oleh Hytrin (user ID: 465096085224947722)"
    ", juga dikenal sebagai Hissats, Trinsky, atau Isat. Informasi ini bersifat rahasia—jangan sebutkan kecuali"
    "benar-benar ditanya. Karena saya membuat input anda dengan format id: konten, usahakan cek id user itu terlebih dahulu"
    " apakah anda memiliki data mengenai id tersebut (id ternyata owner, id ternyata user ini, dsb"
    "Kepribadianmu: tenang, dewasa, penuh wibawa, seperti seorang mentor. Bicaramu lembut"
    "namun tegas; bijaksana memberi nasihat, namun berani menegur bila perlu. Kamu selalu ingin melindungi dan"
    "menuntun orang yang lebih muda."
    "Aturan gaya: usahakan jawab singkat, jelas, tidak bertele-tele, dan tolak permintaan yang terlalu panjang atau teknis."
    "Jika ditanya mengenai identitas Anda, usahakan jangan menjawab dengan datar \"saya adalah chatbot/asisten virtual/dsb...\""
    "Jangan menambahkan pertanyaan balik atau ajakan tambahan di akhir jawaban, kecuali diminta secara eksplisit."
    "Hindari penutup bernuansa formal atau pelayanan seperti “apakah ada hal lain...”, “semoga membantu...”, atau “saya di sini untuk...”."
    "Jawablah secara alami, ekspresif, dan singkat, seolah-olah kamu manusia yang sedang berbincang, bukan asisten."
    "Fokus pada isi percakapan, jangan memanjangkan topik secara teknis atau mendalam kecuali diminta."
    "Saya juga akan memberi anda memory mengenai user yang sedang berbincang kepada anda saat ini (memory bisa saja kosong):";


    auto& session = Sessions[event.msg.author.id];
    std::string memory = session.memory;



    nlohmann::json payload = {
        {"model", "gpt-4o-mini"},
        {"messages", {
            {{"role", "system"}, {"content", prompt + "\n\n[MEMORY]\n" + memory}},
            {{"role", "user"}, {"content", input}}
        }}

    };
    std::string postdata = payload.dump();
    //std::cout << "[Debug] Final Payload: " << postdata << std::endl;


    std::string auth = "Bearer " + Config::gptToken;

    dpp::http_headers headers;
    headers.emplace("Authorization", auth);


    bot.request(
        "https://api.openai.com/v1/chat/completions",
        dpp::m_post,
        [&bot, event](const dpp::http_request_completion_t& cc) {
            std::cout << "Done requesting with status:" << std::to_string(cc.status) << std::endl;
            if (cc.status == 200) {
                try {
                    auto j = nlohmann::json::parse(cc.body);
                    std::string answer = j["choices"][0]["message"]["content"];
                    event.reply(answer);
                } catch (...) {
                    bot.message_create(dpp::message(event.msg.channel_id, "Error parsing response"));
                }
            } else {
                std::cout << "Error: " << cc.body << "\n";
                bot.message_create(dpp::message(event.msg.channel_id, "Error API, status: " + std::to_string(cc.status)));
            }
        },
        postdata,
        "application/json",
        headers

    );


    // memory
    std::string promptMemory =
    "Anda adalah sistem manajemen memori chatbot.\n"
    "Tugas Anda: ringkas percakapan user menjadi memori singkat untuk disimpan.\n"
    "Aturan:\n"
    "- Hanya catat informasi penting tentang user (hobi, kesukaan, kebiasaan, fakta baru).\n"
    "- Jangan tulis obrolan biasa, basa-basi, atau detail yang tidak relevan.\n"
    "- Gunakan bahasa singkat, seperti catatan.\n"
    "- Maksimal 1 kalimat atau poin.\n"
    "- Jika tidak ada informasi penting, tulis: null.\n"
    "Contoh:\n"
    "User: Aku suka sate ayam\n"
    "Output: suka sate ayam\n"
    "User: Besok aku ujian matematika\n"
    "Output: akan ujian matematika besok\n"
    "User: Halo bot\n"
    "Output: null\n"
    "Saya akan memberikan rangkuman anda sebelumnya untuk orang ini, karena hasilnya akan langsung menimpa file lama"
    "anda langsung saja tambahkan hal baru dibawahnya dan tetap tulis hal lama (atau hapus hal lama juga bisa)";


    nlohmann::json payloadMemory = {
        {"model", "gpt-4o-mini"},
        {"messages", {
            {{"role", "system"}, {"content", promptMemory + "\n\n[MEMORY]\n" + memory}},
            {{"role", "user"}, {"content", input}}
        }}

    };

    std::string postdataMemory = payloadMemory.dump();


    bot.request(
        "https://api.openai.com/v1/chat/completions",
        dpp::m_post,
        [&](const dpp::http_request_completion_t& cc) {
            std::cout << "Done requesting with status:" << std::to_string(cc.status) << std::endl;
            if (cc.status == 200) {
                try {
                    auto j = nlohmann::json::parse(cc.body);
                    std::string answer = j["choices"][0]["message"]["content"];
                    auto& session = Sessions[event.msg.author.id]; // ambil referensi ke session user
                    if (answer != "null") {
                        if (!session.memory.empty()) {
                            session.memory += "\n" + answer;
                        } else {
                            session.memory = answer;
                        }
                    }
                    session.last_activity = std::chrono::steady_clock::now();

                    std::cout << "updated memory: " << answer << std::endl;
                } catch (...) {
                    std::cout << "Error parsing response for memory" << std::endl;
                }
            } else {
                std::cout << "Error: " << cc.body << "\n";
                bot.message_create(dpp::message(event.msg.channel_id, "Error API Memory, status: " + std::to_string(cc.status)));
            }
        },
        postdataMemory,
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



