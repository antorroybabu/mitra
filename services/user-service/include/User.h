#pragma once

#include <cstdint>
#include <string>

namespace mitra::user {

struct User {
    std::uint64_t id{0};
    std::string email;
    std::string display_name;
    bool active{true};
};

} // namespace mitra::user
