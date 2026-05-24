#ifndef USER_SESSIONS_H
#define USER_SESSIONS_H

#include "shared/data.h"

#include <string>
#include <chrono>



class UserSessionState {
    public:
    UserSessionState();
    UserSession& Get(const std::string& user_id);
    void Remove(const std::string& user_id);



    private:

};

#endif // USER_SESSIONS_H
