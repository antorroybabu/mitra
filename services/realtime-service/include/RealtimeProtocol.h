#pragma once
#include <cstdint>
#include <string>
namespace mitra::realtime { enum class Type{message,typing,presence,call_offer,call_answer,ice_candidate}; struct Event{std::uint64_t id{},sender_id{},recipient_id{};Type type{Type::message};std::string payload;}; }
