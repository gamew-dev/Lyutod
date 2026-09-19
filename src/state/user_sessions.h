#ifndef USER_SESSIONS_H
#define USER_SESSIONS_H

#include "shared/common.h"

#include <string>
#include <chrono>
#include <unordered_map>
#include <memory>

class UserSessionState {
    public:
    UserSessionState();
    UserSessionStructData& Get(const std::string& user_id);
    void Remove(const std::string& user_id);



    private:
    std::unordered_map<u_int64_t, std::shared_ptr<UserSessionStructData>> data_;

};

#endif // USER_SESSIONS_H
