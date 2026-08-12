#pragma once
#include <cstdint>
#include <string>
namespace mitra::social {
struct User{std::uint64_t id{};std::string username;std::string display_name;};
struct Post{std::uint64_t id{};std::uint64_t author_id{};std::string text;std::int64_t created_at_ms{};};
struct Follow{std::uint64_t follower_id{};std::uint64_t following_id{};};
struct Reaction{std::uint64_t user_id{};std::uint64_t post_id{};std::uint8_t type{};};
struct Comment{std::uint64_t id{};std::uint64_t user_id{};std::uint64_t post_id{};std::string text;std::int64_t created_at_ms{};};
}
