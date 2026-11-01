#ifndef USER_SESSIONS_H
#define USER_SESSIONS_H

#include "shared/common.h"

#include <string>
#include <chrono>
#include <unordered_map>
#include <memory>
#include <mutex>

class UserSessionState {
public:
    UserSessionState() = default;

    bool Has(u_int64_t user_id) const;
    bool Has(const std::string& user_id) const;

    UserSessionStructData& Get(u_int64_t user_id);
    UserSessionStructData& Get(const std::string& user_id);

    std::shared_ptr<UserSessionStructData> GetPtr(u_int64_t user_id);
    std::shared_ptr<UserSessionStructData> GetPtr(const std::string& user_id);

    void Remove(u_int64_t user_id);
    void Remove(const std::string& user_id);

    void Cleanup(std::chrono::minutes max_idle = std::chrono::minutes(10));
    size_t Size() const;
    void Clear();

    template<typename Fn>
    void ForEach(Fn fn) {
        std::lock_guard<std::mutex> lock(mutex_);
        for (auto& [id, session] : data_) {
            fn(id, *session);
        }
    }

private:
    static u_int64_t ParseUserId(const std::string& id_str);

    mutable std::mutex mutex_;
    std::unordered_map<u_int64_t, std::shared_ptr<UserSessionStructData>> data_;
};

#endif // USER_SESSIONS_H
