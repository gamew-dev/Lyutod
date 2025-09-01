#include "Utils.h"

std::string Utils::getRam() {
    std::ifstream core_file("/proc/self/status");
    std::string line;

    while (std::getline(core_file, line)) {
     #ifdef __linux__
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

std::string Utils::getTime(const std::time_t& time) {
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

std::string Utils::getPing(const dpp::cluster& bot) {
    return (std::to_string(int(bot.rest_ping * 100)) + " ms");
}

std::string Utils::clearMention(const std::string& message, const std::string& id) {
    std::string content = message;

    // Pola mention bisa <@id> atau <@!id>
    std::string mention1 = "<@" + id + ">";
    std::string mention2 = "<@!" + id + ">";

    size_t pos;
    while ((pos = content.find(mention1)) != std::string::npos) {
        content.erase(pos, mention1.length());
    }
    while ((pos = content.find(mention2)) != std::string::npos) {
        content.erase(pos, mention2.length());
    }

    // Hilangkan spasi berlebih
    if (!content.empty() && content.front() == ' ')
        content.erase(0, content.find_first_not_of(" "));

    return content;
}



int Utils::getDay() {
    // timenow? (timestamps)
    std::time_t waktu = std::time(nullptr);

    // W.I.B.I.N.I.Z.E.R 7000
    waktu += 7 * 60 * 60;

    // timestamps -> day format (0 - 6)
    std::tm* hari = std::gmtime(&waktu);

    // (0 = minggu, 6 = sabtu)
    return hari->tm_wday;
}

bool Utils::isMentioned(dpp::cluster& bot, const dpp::message_create_t& event) {


    for (const auto& user_mention : event.msg.mentions) {
            if (user_mention.first.id == bot.me.id) {
                return true;
                std::cout << "bot mentioned" << std::endl;
            }
    }


    return false;
}
