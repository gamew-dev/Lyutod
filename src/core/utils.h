#ifndef UTILS_H
#define UTILS_H

//#include "dpp/dpp.h"

#include <string> // std::string
#include <chrono> // std::time_t


namespace dpp {
    class cluster;
    struct message_create_t;
}

namespace utils
{

std::string GetRam(); // get ram size

std::string GetTime(const std::time_t& time)    ; // get online time

std::string GetPing(const dpp::cluster& bot)    ; // get latency

std::string ClearMention(const std::string& message,
                         const std::string& id);

int  GetDay(); // get day (0 - 6) format

bool IsMentioned(dpp::cluster& bot,
                 const dpp::message_create_t& event);
void ChangeChannelName(dpp::cluster& bot,
                       const u_int64_t& channel_id,
                       const std::string& sync_value,
                       const std::string& new_name);

void ChangeChannelName(dpp::cluster& bot,
                       const u_int64_t& channel_id,
                       const std::string& new_name);

}

#endif // UTILS_H
