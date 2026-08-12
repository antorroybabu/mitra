#pragma once

#include <drogon/HttpTypes.h>
#include <string>

namespace mitra::auth {

struct LoginRequest {
    std::string email;
    std::string password;
};

struct AuthResult {
    bool success{false};
    std::string error;
};

// Authentication policy boundary. Persistence and token implementation are
// intentionally kept behind this interface so security-sensitive details can
// be reviewed independently before production use.
class AuthService final {
public:
    AuthResult validate_login_input(const LoginRequest& request) const;
};

} // namespace mitra::auth
