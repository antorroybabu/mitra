#pragma once
#include <cstdint>
#include <string_view>
namespace mitra::observability { struct RequestMetric{std::string_view route;std::uint64_t duration_ms{};std::uint16_t status{};}; struct Counter{std::uint64_t value{};void inc()noexcept{++value;}}; }
