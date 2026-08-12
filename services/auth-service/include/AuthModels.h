#pragma once
#include <cstdint>
#include <string>
namespace mitra::auth { struct PasswordRecord{std::string encoded;}; struct Session{std::uint64_t id{};std::uint64_t user_id{};std::int64_t expires_at_ms{};bool revoked{false};}; }
