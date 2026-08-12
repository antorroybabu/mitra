#pragma once

#include <cstdint>
#include <string>

namespace mitra::feed {

struct Cursor final {
    std::int64_t created_at_ms{0};
    std::uint64_t item_id{0};

    [[nodiscard]] bool valid() const noexcept {
        return created_at_ms > 0 && item_id > 0;
    }
};

// Stable opaque representation can be added at the API boundary. The
// internal cursor deliberately uses a timestamp + unique ID tie-breaker so
// pagination remains deterministic when many items share a timestamp.
} // namespace mitra::feed
