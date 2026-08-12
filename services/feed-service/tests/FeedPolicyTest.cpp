#include "../include/FeedPolicy.h"

#include <cassert>

int main() {
    using namespace mitra::feed;
    FeedPolicy policy;
    FeedRequest request{42, 1000, 50};
    assert(valid(request, policy));

    request.user_id = 0;
    assert(!valid(request, policy));

    request.user_id = 42;
    policy.page_size = 101;
    assert(!valid(request, policy));
    return 0;
}
