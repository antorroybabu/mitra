#include "AuthService.h"

#include <algorithm>
#include <cctype>

namespace mitra::auth {

AuthResult AuthService::validate_login_input(const LoginRequest& request) const {
    if (request.email.empty() || request.password.empty()) {
        return {false, "invalid credentials"};
    }

    if (request.email.size() > 320 || request.password.size() > 1024) {
        return {false, "invalid credentials"};
    }

    const auto at = request.email.find('@');
    if (at == std::string::npos || at == 0 || at + 1 >= request.email.size()) {
        return {false, "invalid credentials"};
    }

    return {true, {}};
}

} // namespace mitra::auth
