#pragma once
#include "CandidateGenerator.h"
#include <cstddef>
#include <cstdint>
#include <unordered_set>
#include <vector>
namespace mitra::recommendation {
class FollowGraph final {
public:
 void follow(std::uint64_t user,std::uint64_t creator){ if(user&&creator) following_[user].insert(creator); }
 void unfollow(std::uint64_t user,std::uint64_t creator){ auto it=following_.find(user); if(it!=following_.end()) it->second.erase(creator); }
 [[nodiscard]] bool follows(std::uint64_t user,std::uint64_t creator) const { auto it=following_.find(user); return it!=following_.end()&&it->second.contains(creator); }
private:
 std::unordered_map<std::uint64_t,std::unordered_set<std::uint64_t>> following_;
};
}
