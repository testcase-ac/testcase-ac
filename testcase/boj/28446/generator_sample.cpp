#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Request {
    int type;
    int x;
    int w;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int insert_count = rnd.next(1, 25);
    int query_count = rnd.next(1, min(25, insert_count * 2));

    vector<int> lockers;
    vector<int> weights;
    lockers.reserve(insert_count);
    weights.reserve(insert_count);

    for (int i = 0; i < insert_count; ++i) {
        int x;
        if (mode == 0) {
            x = i + 1;
        } else if (mode == 1) {
            x = 1000000 - i;
        } else if (mode == 2) {
            x = rnd.next(1, 7);
        } else {
            x = rnd.next(1, 1000000);
        }
        lockers.push_back(x);

        int w;
        if (mode == 1) {
            w = 1000000000 - i;
        } else if (mode == 3 && i < 3) {
            static const int edge_weights[] = {1, 1000000000, 999999999};
            w = edge_weights[i];
        } else {
            w = 10 + i * 37 + rnd.next(0, 20);
        }
        weights.push_back(w);
    }

    shuffle(weights.begin(), weights.end());

    vector<Request> requests;
    requests.reserve(insert_count + query_count);

    int inserted = 0;
    int remaining_queries = query_count;
    while (inserted < insert_count || remaining_queries > 0) {
        bool must_insert = inserted == 0 || (inserted < insert_count && rnd.next(0, 99) < 55);
        if (must_insert || remaining_queries == 0) {
            requests.push_back({1, lockers[inserted], weights[inserted]});
            ++inserted;
        } else {
            int idx = rnd.next(0, inserted - 1);
            requests.push_back({2, 0, weights[idx]});
            --remaining_queries;
        }
    }

    println(static_cast<int>(requests.size()));
    for (const Request& request : requests) {
        if (request.type == 1) {
            println(1, request.x, request.w);
        } else {
            println(2, request.w);
        }
    }

    return 0;
}
