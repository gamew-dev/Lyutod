#include "responses_chat.h"

#include <random>
#include <ctime>

#include "dpp/unicode_emoji.h"

namespace responses_chat {

    const std::vector<std::string> emot = {
        dpp::unicode_emoji::pleading_face,
        dpp::unicode_emoji::nerd,
        dpp::unicode_emoji::melting_face,
        dpp::unicode_emoji::thinking_face,
        dpp::unicode_emoji::skull,
        dpp::unicode_emoji::zany_face,
        dpp::unicode_emoji::dizzy_face,
        dpp::unicode_emoji::face_with_spiral_eyes,
        dpp::unicode_emoji::face_exhaling,
        dpp::unicode_emoji::expressionless,
        dpp::unicode_emoji::rolling_eyes,
        dpp::unicode_emoji::open_mouth,
        dpp::unicode_emoji::pleading_face,
        dpp::unicode_emoji::weary,
        dpp::unicode_emoji::confounded
    };

    const std::vector<std::string> emot2 = {
        dpp::unicode_emoji::pregnant_man,
        dpp::unicode_emoji::eggplant,
        dpp::unicode_emoji::fish,
        dpp::unicode_emoji::wilted_flower
    };


    std::string GetEmote() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, emot.size() - 1);

        return emot[distrib(gen)];
    }


    std::string HandleMessage(std::string_view text) {

        // i think i should've used else if instead of all if, we'll do that later ^_^
        if (
            text == "halo" || text == "hai"  ||
            text == "woi"  || text == "hi"    )
            {
                return "sapa";
            }

        if (
            text.find("jawa")  != std::string::npos || text.find("jwa") != std::string::npos  ||
            text.find("jw")    != std::string::npos || text.find("jaua") != std::string::npos )
            {
                return "react";
            }

        if (
            text == "sefi" || text == "sfi"   ||
            text == "sepi" || text == "spi"    )
            {
                return "sepi";
            }

        if (
            text == "pagi" || text == "pgi")
            {
                return "pagi";
            }

        if (
            text == "siang" || text == "siyang")
            {
                return "siang";
            }

        if (
            text == "sore" || text == "sre" || text == "petang")
            {
                return "sore";
            }

        if (
            text == "malam" || text == "mlm" || text == "mlam")
            {
                return "malam";
            }

        if (
            text == "bobok" || text == "bbok"  || text == "bbk"   ||
            text == "boobk" || text == "obbok" || text == "bobko" ||
            text == "turu"  || text == "turu"  || text == "tr"    ||
            text == "tuur"  || text == "utru"  || text == "bobko"  )
            {
                return "bobok";
            }

        /// Shutdown command
        //  this one is unique, instead of using slash command Im using this, why? well its cool tho
        //  the function is still experiment and i dont know hos stable it is
        //  usage: shutdown <option>
        //  ex: shutdown now, shutdown 30s, shutdown 5m, other than that it will be treated as default: 60s
        /*
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
            */

            return "prohibited";

        }
    }

    std::string MakeMessage(std::string_view keyword,
                            std::string_view user_nick,
                            const std::string& user_id,
                            bool mention) {

        //std::cout << "log: keyword = " << keyword << std::endl;

        auto cari = responses_chat::pilihan.find(keyword);
        if (cari == responses_chat::pilihan.end() || cari->second.empty()) {
            // keyword not found :bobok:
            return "aoa cona";
        }

        // random generator
        static std::mt19937 rng(static_cast<unsigned int>(std::time(nullptr)));
        std::uniform_int_distribution<> dist(0, static_cast<int>(cari->second.size()) - 1);

        std::string jawab = cari->second[dist(rng)];

        // ganti placeholder {user}
        const std::string placeholder = "{user}";
        size_t pos = jawab.find(placeholder);

        if (pos != std::string::npos) {
            std::string pengganti = mention ? ("<@"+user_id+">") : user_nick;
            jawab.replace(pos, placeholder.length(), pengganti);
        }

        /*
        // Tambahan reaksi hari Sabtu & Minggu
        int hari = Utils::getDay();
        if (hari == 6 && !Config::cooldownBsok) { // Sabtu
            jawab += "\nbsok minggu <a:a_nice:1370082910991945778>";
            Config::cooldownBsok = true;
        } else if (hari == 0 && !Config::cooldownBsok) { // Minggu
            jawab += "\nbsok senin <:mengsedih:1370066473959297024>";
            Config::cooldownBsok = true;
        }
        */
        return jawab;
    }

}
