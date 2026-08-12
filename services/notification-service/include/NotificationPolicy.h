#pragma once
#include <cstdint>
namespace mitra::notification { enum class Type{like,comment,follow,mention,system}; struct Notification{std::uint64_t id{},recipient_id{},actor_id{},object_id{};Type type{Type::system};}; }
