#include "../include/PasswordPolicy.h"
#include "../include/SessionStore.h"
#include "../include/RateLimiter.h"
#include <cassert>
int main(){using namespace mitra::auth;assert(valid_password("StrongPass9!x"));assert(!valid_password("weak"));SessionStore s;assert(s.create({1,42,999999,false}));assert(s.get(1)&&!s.get(1)->revoked);assert(s.revoke(1));assert(s.get(1)->revoked);RateLimiter r(2,0);assert(r.allow(42));assert(r.allow(42));assert(!r.allow(42));return 0;}
