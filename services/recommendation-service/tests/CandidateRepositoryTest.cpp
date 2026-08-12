#include "../include/CandidateRepository.h"
#include <cassert>
int main(){ using namespace mitra::recommendation; FollowGraph graph; CandidateIndex index; graph.follow(7,42); index.upsert({100,42,1,{"tech"}}); index.upsert({101,42,2,{"tech"}}); CandidateRepository repo(index,graph); auto result=repo.following(7,10,10); assert(result.size()==2); assert(result[0].content_id!=result[1].content_id); return 0; }
