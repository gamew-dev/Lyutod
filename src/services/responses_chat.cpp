#include "responses_chat.h"

#include "dpp/dpp.h"


namespace responses_chat {

    std::string EmoteReact() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, emot.size() - 1);

        return emot[distrib(gen)];
    }


    bool HandleMessage(std::string_view text) {
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
                //std::clog << "react test" << std::endl;
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
                            .set_emoji(Responses::emoteReact())
                            .set_style(dpp::cos_success )

                            .set_id("ID_tes")
                    )
                );

                bot.message_create(aaa,[&](const dpp::confirmation_callback_t& cb) {
                    if (cb.is_error()) return;

                    const dpp::message& sent = std::get<dpp::message>(cb.value);

                    MessageSessionStruct session;
                        session.owner = event.msg.author.id;
                        session.type = "testttttt";
                        session.state = "stateless";
                        session.page = -1;
                        session.last_activity = std::chrono::steady_clock::now();

                    MessageSession[sent.id] = session;

                });


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

                //std::cout << "[Debug]: original input: " << text << std::endl;
                // cut the shutdown string
                std::string arg = text.substr(9);
                std::stringstream ss(arg);
                std::string option;
                ss >> option;
                //std::cout << "[Debug]: cutted input: (arg: " << arg << " , option: " << option << ")" << std::endl;

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

    std::string MakeMessage(const std::string& keyword,
                            const dpp::user& user,
                            const bool& mention) {

        //std::cout << "log: keyword = " << keyword << std::endl;

        auto cari = Responses::pilihan.find(keyword);
        if (cari == Responses::pilihan.end() || cari->second.empty()) {
            // keyword not found :bobok:
            return "<@"+Config::botOwner+">";
        }

        // random generator
        static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<> dist(0, static_cast<int>(cari->second.size()) - 1);

        std::string jawab = cari->second[dist(rng)];

        // ganti placeholder {user}
        const std::string placeholder = "{user}";
        size_t pos = jawab.find(placeholder);

        if (pos != std::string::npos) {
            std::string pengganti = mention ? user.get_mention() : user.username;
            jawab.replace(pos, placeholder.length(), pengganti);
        }

        // Tambahan reaksi hari Sabtu & Minggu
        int hari = Utils::getDay();
        if (hari == 6 && !Config::cooldownBsok) { // Sabtu
            jawab += "\nbsok minggu <a:a_nice:1370082910991945778>";
            Config::cooldownBsok = true;
        } else if (hari == 0 && !Config::cooldownBsok) { // Minggu
            jawab += "\nbsok senin <:mengsedih:1370066473959297024>";
            Config::cooldownBsok = true;
        }

        return jawab;
    }

}
