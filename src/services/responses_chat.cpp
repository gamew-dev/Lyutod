#include "responses_chat.h"

#include "dpp/dpp.h"


namespace responses_chat {

    std::string EmoteReact() {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, emot.size() - 1);

        return emot[distrib(gen)];
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
