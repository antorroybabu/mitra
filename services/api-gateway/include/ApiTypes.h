#pragma once
#include <cstdint>
#include <string>
namespace mitra::api { struct Error{std::string code;std::string message;}; struct AuthenticatedRequest{std::uint64_t user_id{};}; struct PageInfo{bool has_next{false};std::string next_cursor;}; }
