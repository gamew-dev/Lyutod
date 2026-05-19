#ifndef RESPONSES_H
#define RESPONSES_H

#include "dpp/unicode_emoji.h"

#include <random>


namespace responses_chat
{

    //std::string EmoteReact();
    std::string GetEmote();
    std::string HandleMessage(std::string_view text);
    std::string MakeMessage(std::string_view keyword,
                            std::string_view user_nick,
                            std::string_view user_id,
                            bool mention);


    std::unordered_map<std::string, std::vector<std::string>> pilihan = {
        {"sambut", // greet
            {
            "{user} hai sayang! <:wlwl:1370068430316765264>",
            "halo bubub {user} <:lup:1370432773814227014>",
            "woe anak mana loe {user} <:hmm:1370308187399520289>",
            "{user} member baru sungkem dulu sini ya <:y_y:1370304542914383924>",
            "awww {user}, yuk kenalan dulu.. <:waa:1370433197913145455>",
            "aww ada {user}, aku jadi malu <:aww:1370432517211033791>"
            }
        },
        {"panggil", // pinged (unused if used ai)
            {
            "nggih?", "apasih", "Halo, {user}. Bagaimana kabarmu?",
            "<:hadir:1370082147834003528>", "<:ndatawu:1370304357052186624>", "iya halo", "gimanah?"
            }
        },
        {"sepi", // dead chat
            {
            "iyh <:turu:1370067202635595817>", "y", "Halo, {user}. Bagaimana kabarmu?",
            "<:hadir:1370082147834003528>", "<:ndatawu:1370304357052186624>"
            }
        },
        {"sapa", {
            "halo juga {user}", "hai hai ^_^", "halo {user}, bagaimana kabarmu?",
            "<:iyah:1370304877615386704> halo"
        }},
        {"pagi", {
            "pagi juga {user}", "jangan bobok lagi yah", "tumben dah bangun",
            "lanjut turu", "hooh"
        }},
        {"siang", {
            "siang {user}", "bobok", "ngopi", "turu turu", "y"
        }},
        {"sore", {
            "sore sore jangan turu yah {user}", "sok asik", "mending masak mie",
            "infokan mabaw", "ngopi", "login", "<:iyah:1370304877615386704>"
        }},
        {"malam", {
            "malam juga {user}", "jangan begadang yach {user}", "bobok",
            "turu besok kerja", "iyaa, malam juga sayang ^_^", "turu",
            "<:wlwl:1370068430316765264>", "<:turu:1370067202635595817>"
        }},
        {"bobok", {
            "nggih monggo", "turu turu", "nanggung begadang ae",
            "mnding mabaw", "<:turu:1370067202635595817>"
        }},
        {"invite", {
            "hai sayank", "aku datang", "<:y_y:1370304542914383924>",
            "p", "peace be upon you <:lup:1370432773814227014>"
        }},
        { "prohibited", {
            "hmm", "sok asik", "luwh siapa", "wleee",
            "anda tidak memiliki ijin untuk menjalankan perintah tersebut, hal ini akan dilaporkan ke pihak developer",
            "<:y_y:1370304542914383924>", "<:apalah:1370304744316469249>"
        }},
        { "confirmed", {
            "k", "siap bos", "nggih", "olraikk",
            "don",
            "otw", "emuachh"
        }}
    };
    // this is for react
    extern const std::vector<std::string> emot;

    extern const std::vector<std::string> emot2;
}

#endif // RESPONSES_H
