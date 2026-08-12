#pragma once
#include "AuthModels.h"
#include <cstdint>
#include <unordered_map>
namespace mitra::auth { class SessionStore final { public: bool create(Session s){if(!s.id||!s.user_id)return false;return sessions_.emplace(s.id,s).second;} bool revoke(std::uint64_t id){auto i=sessions_.find(id);if(i==sessions_.end())return false;i->second.revoked=true;return true;} const Session* get(std::uint64_t id)const{auto i=sessions_.find(id);return i==sessions_.end()?nullptr:&i->second;} private:std::unordered_map<std::uint64_t,Session> sessions_;}; }
