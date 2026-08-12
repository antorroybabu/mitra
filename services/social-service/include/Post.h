#pragma once

#include <cstdint>
#include <string>

namespace mitra::social {

struct Post final {
    std::uint64_t id{0};
    std::uint64_t author_id{0};
    std::string text;
};

} // namespace mitra::social
