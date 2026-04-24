#include "testlib.h"
#include <vector>
using namespace std;

struct Query {
    int type;
    long long param;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for sizes
    int N = rnd.next(2, 10);          // number of type-1 arrivals
    int R = rnd.next(0, N - 1);       // number of type-2 removals
    int E = rnd.next(1, N * 2);       // number of type-3 events

    // Hyper-parameter for x distribution
    bool smallX = rnd.next(0, 1);

    vector<Query> qs;
    vector<int> active;               // list of active student IDs
    int nextId = 1;
    int left1 = N, left2 = R, left3 = E;

    // Build a valid sequence
    while (left1 + left2 + left3 > 0) {
        vector<int> types;
        if (left1 > 0) types.push_back(1);
        if (left2 > 0 && !active.empty()) types.push_back(2);
        if (left3 > 0) types.push_back(3);
        int t = rnd.any(types);
        if (t == 1) {
            // Arrival with number x
            int x;
            if (smallX) {
                x = rnd.next(1, 10);
            } else {
                int w = rnd.next(-1, 1);
                x = rnd.wnext(1000000, w) + 1;
            }
            qs.push_back({1, x});
            active.push_back(nextId++);
            left1--;
        } else if (t == 2) {
            // Removal of a random active student
            int idx = rnd.next(0, (int)active.size() - 1);
            int k = active[idx];
            qs.push_back({2, k});
            active.erase(active.begin() + idx);
            left2--;
        } else {
            // Event with bonus s
            int w = rnd.next(-1, 1);
            long long s = (long long)rnd.wnext(1000000000, w) + 1;
            qs.push_back({3, s});
            left3--;
        }
    }

    // Output
    println((int)qs.size());
    for (auto &q : qs) {
        println(q.type, q.param);
    }
    return 0;
}
