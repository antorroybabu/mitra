#pragma once

#include <string>

namespace mitra::auth {

class PasswordHasher final {
public:
    // Production implementation must use a vetted password KDF such as
    // Argon2id. This interface keeps the choice out of HTTP controllers.
    std::string hash(const std::string& password) const;
    bool verify(const std::string& password, const std::string& encoded_hash) const;
};

} // namespace mitra::auth
