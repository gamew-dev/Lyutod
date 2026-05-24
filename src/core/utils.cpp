#include "utils.h"

#include "dpp/dpp.h"

#include "config.h"

namespace utils {

std::string GetRam() {

    #ifdef __linux__
    std::ifstream core_file("/proc/self/status");
    std::string line;

    while (std::getline(core_file, line)) {
        if (line.find("VmRSS:") == 0) {
            std::istringstream iss(line);
            std::string label, unit;
            int kb_value;

            iss >> label >> kb_value >> unit;
            double mb_value = static_cast<double>(kb_value) / 1024.0;

            std::ostringstream result;
            result.precision(2);
            result << std::fixed << mb_value << " MB";
            return result.str();
        }
    }

    #elif _WIN32
        // yo ndaktawu, tanya kok tanya saya
        PROCESS_MEMORY_COUNTERS memInfo;
        GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
        return memInfo.WorkingSetSize / 1024;
    #endif

    return "???";
}

std::string GetTime(const std::time_t& time) {
    std::time_t now = std::time(nullptr);
    std::time_t diff = now - time;

    int days = diff / (24 * 3600);
    diff %= (24 * 3600);
    int hours = diff / 3600;
    diff %= 3600;
    int minutes = diff / 60;
    int seconds = diff % 60;

    std::ostringstream result;
    if (days > 0) {
        result << days << " Hari, " << hours << " jam, " << minutes << " menit";
    } else {
        result << hours << " Jam, " << minutes << " menit, " << seconds << " detik";
    }

    return result.str();
}

std::string GetPing(const dpp::cluster& bot) {
    return (std::to_string(int(bot.rest_ping * 100)) + " ms");
}

std::string ClearMention(const std::string& message, const std::string& id) {
    std::string content = message;


    std::string mention1 = "<@" + id + ">";
    std::string mention2 = "<@!" + id + ">";

    size_t pos;
    while ((pos = content.find(mention1)) != std::string::npos) {
        content.erase(pos, mention1.length());
    }
    while ((pos = content.find(mention2)) != std::string::npos) {
        content.erase(pos, mention2.length());
    }

    if (!content.empty() && content.front() == ' ')
        content.erase(0, content.find_first_not_of(" "));

    return content;
}



int GetDay() {
    // timenow? (timestamps)
    std::time_t waktu = std::time(nullptr);

    // W.I.B.I.N.I.Z.E.R 7000
    waktu += 7 * 60 * 60;

    // timestamps -> day format (0 - 6)
    std::tm* hari = std::gmtime(&waktu);

    // (0 = minggu, 6 = sabtu)
    return hari->tm_wday;
}

bool isMentioned(dpp::cluster& bot, const dpp::message_create_t& event) {


    for (const auto& user_mention : event.msg.mentions) {
            if (user_mention.first.id == bot.me.id) {
                return true;
                if (config::isLog) std::cout << "bot mentioned" << std::endl;
            }
    }


    return false;
}

void voidCchangeChannelname( dpp::cluster& bot,
                              const dpp::snowflake& channel_id,
                              const std::string& sync_value,
                              const std::string& new_name) {

    bot.channel_get(channel_id, [&bot, sync_value, new_name](const dpp::confirmation_callback_t& cc) {
        if (!cc.is_error()) {

            dpp::channel ch = std::get<dpp::channel>(cc.value);
            std::string finalName;

            if (new_name == "") {
                std::string base = ch.name.substr(0, ch.name.find(" : "));
                finalName = base + " : " + sync_value;
            } else {
                finalName = new_name + " : " + sync_value;
            }

            ch.set_name(finalName);

            bot.channel_edit(ch, [](const dpp::confirmation_callback_t& cc2) {
                if (cc2.is_error()) {
                    //if (config::isLog) std::cout << "[Debug]: human only error..." << std::endl;

                } else {
                    //if (config::isLog) std::cout << "[Debug]: human only updated..." << std::endl;;

                }

            });
        } else {
            //if (config::isLog) std::cout << "[Debug]: Error get human channel" << std::endl;
        }
    });
}

void ChangeChannelname(dpp::cluster& bot,
                                    const dpp::snowflake& channel_id,
                                    const std::string& new_name) {

    bot.channel_get(channel_id, [&bot, new_name](const dpp::confirmation_callback_t& cc) {
        if (!cc.is_error()) {

            dpp::channel ch = std::get<dpp::channel>(cc.value);

            ch.set_name(new_name);

            bot.channel_edit(ch, [](const dpp::confirmation_callback_t& cc2) {
                if (cc2.is_error()) {
                    if (config::isLog) std::cout << "[Debug]: human only error..." << std::endl;

                } else {
                    if (config::isLog) std::cout << "[Debug]: human only updated..." << std::endl;

                }

            });
        } else {
            if (config::isLog) std::cout << "[Debug]: Error get human channel" << std::endl;
        }
    });

}

}
