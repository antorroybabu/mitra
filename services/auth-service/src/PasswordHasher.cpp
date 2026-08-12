#include "PasswordHasher.h"

#include <stdexcept>

namespace mitra::auth {

std::string PasswordHasher::hash(const std::string& password) const {
    if (password.empty()) {
        throw std::invalid_argument("password must not be empty");
    }

    // Deliberately fail closed until the vetted Argon2id dependency is wired
    // into the build. Never substitute a fast hash such as SHA-256 here.
    throw std::runtime_error("password KDF dependency is not configured");
}

bool PasswordHasher::verify(const std::string& password,
                            const std::string& encoded_hash) const {
    if (password.empty() || encoded_hash.empty()) {
        return false;
    }

    // Fail closed for the same reason as hash().
    return false;
}

} // namespace mitra::auth
