#ifndef BUTTON_SESSIONS_H
#define BUTTON_SESSIONS_H

#include "shared/common.h"

#include <string>
#include <chrono>
#include <unordered_map>
#include <mutex>

class ButtonSessionState {
public:
    ButtonSessionState() = default;

    bool Has(const std::string& event_id) const;
    bool Has(u_int64_t message_id) const;

    ButtonSessionStructData& Get(const std::string& event_id);
    ButtonSessionStructData& Get(u_int64_t message_id);

    void Set(const std::string& event_id, const ButtonSessionStructData& session);
    void Set(u_int64_t message_id, const ButtonSessionStructData& session);

    void Remove(const std::string& event_id);
    void Remove(u_int64_t message_id);

    void Cleanup(std::chrono::minutes max_idle = std::chrono::minutes(15));
    size_t Size() const;
    void Clear();

private:
    mutable std::mutex mutex_;
    std::unordered_map<std::string, ButtonSessionStructData> data_;
};

#endif // BUTTON_SESSIONS_H
