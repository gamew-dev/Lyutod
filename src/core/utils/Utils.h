#ifndef UTILS_H
#define UTILS_H

#include "dpp/dpp.h"

namespace Utils
{

    std::string getRam()                            , // get ram size

                    getTime(const std::time_t& time)    , // get online time

                    getPing(const dpp::cluster& bot)    , // get latency

                    clearMention(const std::string& message, const std::string& id);

    int  getDay()                            ; // get day (0 - 6) format

    bool isMentioned(dpp::cluster& bot, const dpp::message_create_t& event);
    void changeChannelname(dpp::cluster& bot,
                                    const dpp::snowflake& channel_id,
                                    const std::string& sync_value,
                                    const std::string& new_name);

    void changeChannelname(dpp::cluster& bot,
                                    const dpp::snowflake& channel_id,
                                    const std::string& new_name);

}

#endif // UTILS_H
