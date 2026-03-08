#ifndef USER_SESSIONS_H
#define USER_SESSIONS_H

#include <string>
#include <chrono>


namespace dpp {

}

struct UserSession {
    std::string memory;
    std::chrono::steady_clock::time_point last_activity;
};

class UserSessionState {
    public:
    UserSession& Get(const std::string& user_id);
    void Remove(const std::string& user_id);



    private:

};

#endif // USER_SESSIONS_H
