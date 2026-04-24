#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of distinct students
    int U = rnd.next(1, 10);
    // Capacity K
    int K = rnd.next(1, U);
    // Total clicks L = U + extra
    int extra = rnd.next(0, 20);
    int L = U + extra;

    // Generate U unique 8-digit IDs
    set<int> sid;
    while ((int)sid.size() < U) {
        sid.insert(rnd.next(0, 99999999));
    }
    vector<int> ids(sid.begin(), sid.end());

    // Initial one click per student in random order
    vector<int> click;
    vector<int> order(U);
    for (int i = 0; i < U; i++) order[i] = i;
    shuffle(order.begin(), order.end());
    for (int x : order) click.push_back(x);

    // Pick hotspots for duplicates
    int burstCount = rnd.next(1, max(1, U/2));
    shuffle(order.begin(), order.end());
    vector<int> hotspots(order.begin(), order.begin() + burstCount);
    double burstProb = rnd.next(0.3, 0.8);

    // Generate extra clicks
    for (int i = 0; i < extra; i++) {
        int idx;
        if (rnd.next() < burstProb) {
            idx = rnd.any(hotspots);
        } else {
            idx = rnd.next(0, U - 1);
        }
        click.push_back(idx);
    }

    // Output
    println(K, L);
    for (int idx : click) {
        // print 8-digit with leading zeros
        printf("%08d\n", ids[idx]);
    }
    return 0;
}
