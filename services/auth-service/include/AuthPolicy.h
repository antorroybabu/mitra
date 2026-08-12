#pragma once

#include <cstddef>

namespace mitra::auth {

struct AuthPolicy final {
    static constexpr std::size_t max_email_length = 320;
    static constexpr std::size_t max_password_length = 1024;
    static constexpr std::size_t max_display_name_length = 100;
    static constexpr int max_login_attempts_per_window = 5;
    static constexpr int login_window_seconds = 300;
};

} // namespace mitra::auth
