#include "../include/SocialValidation.h"
#include <cassert>
int main(){using namespace mitra::social;assert(valid_username("antor_roy"));assert(!valid_username("a"));assert(!valid_username("bad name"));assert(valid_post("hello"));assert(!valid_post(""));assert(valid_page_size(20));assert(!valid_page_size(101));return 0;}
