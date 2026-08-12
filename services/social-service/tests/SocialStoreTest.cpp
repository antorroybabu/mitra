#include "../include/SocialStore.h"
#include <cassert>
int main(){using namespace mitra::social;SocialStore s;assert(s.create_user({1,"antor","Antor Roy"}));assert(s.create_user({2,"user2","User Two"}));assert(s.create_post({10,2,"hello",1}));assert(s.follow(1,2));assert(!s.follow(1,1));assert(s.like(1,10));assert(!s.like(1,10));assert(s.unlike(1,10));assert(s.unfollow(1,2));return 0;}
