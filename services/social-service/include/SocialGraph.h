#pragma once

#include <cstdint>

namespace mitra::social {

struct FollowEdge final {
    std::uint64_t follower_id{0};
    std::uint64_t followed_id{0};
};

} // namespace mitra::social
