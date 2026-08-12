#include "../include/FeedCursor.h"
#include "../include/FeedRequest.h"
#include <cassert>
int main(){using namespace mitra::feed;FeedCursor c{123456,987};auto encoded=encode_cursor(c);auto decoded=decode_cursor(encoded);assert(decoded&&decoded->created_at_ms==c.created_at_ms&&decoded->id==c.id);assert(!decode_cursor("bad"));assert(valid({42,20,decoded}));assert(!valid({0,20,std::nullopt}));assert(!valid({42,101,std::nullopt}));return 0;}
