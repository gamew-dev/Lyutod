#ifndef UTILS_H
#define UTILS_H

#include "dpp/dpp.h"

class Utils
{
    public:

    static std::string getRam()                            , // get ram size

                    getTime(const std::time_t& time)    , // get online time

                    getPing(const dpp::cluster& bot)    ; // get latency

        static int  getDay()                            ; // get day (0 - 6) format

};

#endif // UTILS_H
