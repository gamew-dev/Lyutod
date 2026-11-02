#ifndef SERVER_SESSIONS_H
#define SERVER_SESSIONS_H

/// A struct to pair with ServerSession map for chatbotSession
//  keeps the chat history, last chat, last chat channel id
//  and token usage

#include "shared/common.h"

#include <chrono>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <mutex>

// Server session object wrapped as class
class ServerSessionState {
public:
  ServerSessionState() = default;

  bool Has(u_int64_t guild_id) const;
  ServerSessionStructData& Get(u_int64_t guild_id);
  std::shared_ptr<ServerSessionStructData> GetPtr(u_int64_t guild_id);
  void Remove(u_int64_t guild_id);
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
  mutable std::mutex mutex_;
  std::unordered_map<u_int64_t, std::shared_ptr<ServerSessionStructData>> data_;
};

#endif // SERVER_SESSIONS_H
