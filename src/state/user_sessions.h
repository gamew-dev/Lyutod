#ifndef USER_SESSIONS_H
#define USER_SESSIONS_H

#include "shared/common.h"

#include <string>
#include <chrono>



class UserSessionState {
    public:
    UserSessionState();
    UserSessionStructData& Get(const std::string& user_id);
    void Remove(const std::string& user_id);



    private:

};

#endif // USER_SESSIONS_H
