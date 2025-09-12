#ifndef RESPONSES_H
#define RESPONSES_H

#include "dpp/dpp.h"
#include "dpp/unicode_emoji.h"
#include "Utils.h"

#include <random>

class Responses
{
    public:

    static std::string emoteReact() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, emot.size() - 1);

        return emot[distrib(gen)];
    }

    static std::string makeMsg(const std::string& keyword, const dpp::user& user, bool mention) {
        //std::cout << "log: keyword = " << keyword << std::endl;

        auto cari = Responses::pilihan.find(keyword);
        if (cari == Responses::pilihan.end() || cari->second.empty()) {
            // keyword not found :bobok:
            return "<@465096085224947722>";
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


    private:

    static inline std::unordered_map<std::string, std::vector<std::string>> pilihan = {
        {"sambut", {
            "{user} hai sayang! <:wlwl:1370068430316765264>",
            "halo bubub {user} <:lup:1370432773814227014>",
            "woe anak mana loe {user} <:hmm:1370308187399520289>",
            "{user} member baru sungkem dulu sini ya <:y_y:1370304542914383924>",
            "awww {user}, yuk kenalan dulu.. <:waa:1370433197913145455>",
            "aww ada {user}, aku jadi malu <:aww:1370432517211033791>"
        }},
        {"panggil", {
            "nggih?", "apasih", "Halo, {user}. Bagaimana kabarmu?",
            "<:hadir:1370082147834003528>", "<:ndatawu:1370304357052186624>", "iya halo", "gimanah?"
        }},
        {"sepi", {
            "iyh <:turu:1370067202635595817>", "y", "Halo, {user}. Bagaimana kabarmu?",
            "<:hadir:1370082147834003528>", "<:ndatawu:1370304357052186624>"
        }},
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
        }}
    };
    // this is for react
    static inline std::vector<std::string> emot = {
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

};

#endif // RESPONSES_H
