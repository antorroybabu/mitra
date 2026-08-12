#pragma once
#include <cstdint>
namespace mitra::core { struct RequestId { std::uint64_t value{}; explicit operator bool() const noexcept { return value != 0; } }; }
