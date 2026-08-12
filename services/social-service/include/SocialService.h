#pragma once
#include "SocialStore.h"
#include <cstdint>
#include <string>
namespace mitra::social {
class SocialService final {
public:
 explicit SocialService(SocialStore& store):store_(store){}
 bool register_user(std::uint64_t id,std::string username,std::string display){return store_.create_user({id,std::move(username),std::move(display)});}
 bool publish(std::uint64_t id,std::uint64_t author,std::string body,std::int64_t now){return store_.create_post({id,author,std::move(body),now});}
 bool follow(std::uint64_t user,std::uint64_t creator){return store_.follow(user,creator);}
 bool unfollow(std::uint64_t user,std::uint64_t creator){return store_.unfollow(user,creator);}
 bool like(std::uint64_t user,std::uint64_t post){return store_.like(user,post);}
 bool unlike(std::uint64_t user,std::uint64_t post){return store_.unlike(user,post);}
private: SocialStore& store_;
};
}
