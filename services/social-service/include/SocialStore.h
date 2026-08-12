#pragma once
#include "SocialModels.h"
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <vector>
namespace mitra::social {
class SocialStore final {
public:
 bool create_user(User user){if(!user.id||user.username.empty())return false;return users_.emplace(user.id,std::move(user)).second;}
 bool create_post(Post post){if(!post.id||!post.author_id||!users_.contains(post.author_id))return false;return posts_.emplace(post.id,std::move(post)).second;}
 bool follow(std::uint64_t a,std::uint64_t b){if(!users_.contains(a)||!users_.contains(b)||a==b)return false;return follows_[a].insert(b).second;}
 bool unfollow(std::uint64_t a,std::uint64_t b){auto i=follows_.find(a);return i!=follows_.end()&&i->second.erase(b)>0;}
 bool like(std::uint64_t u,std::uint64_t p){if(!users_.contains(u)||!posts_.contains(p))return false;return likes_[p].insert(u).second;}
 bool unlike(std::uint64_t u,std::uint64_t p){auto i=likes_.find(p);return i!=likes_.end()&&i->second.erase(u)>0;}
 [[nodiscard]] std::vector<std::uint64_t> following(std::uint64_t u)const{std::vector<std::uint64_t>r;auto i=follows_.find(u);if(i==follows_.end())return r;r.assign(i->second.begin(),i->second.end());return r;}
private:
 std::unordered_map<std::uint64_t,User> users_;std::unordered_map<std::uint64_t,Post> posts_;std::unordered_map<std::uint64_t,std::unordered_set<std::uint64_t>> follows_;std::unordered_map<std::uint64_t,std::unordered_set<std::uint64_t>> likes_;
};
}
