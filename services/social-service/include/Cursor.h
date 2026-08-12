#pragma once
#include <cstdint>
#include <optional>
#include <string>
namespace mitra::social {
struct Cursor{std::int64_t created_at_ms{};std::uint64_t id{};};
inline bool before(const Cursor&a,const Cursor&b)noexcept{return a.created_at_ms<b.created_at_ms||(a.created_at_ms==b.created_at_ms&&a.id<b.id);}
}
