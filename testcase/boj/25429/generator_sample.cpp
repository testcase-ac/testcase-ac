#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<long long, long long>> shapes = {
        {1, 1},
        {6, 1},
        {6, 2},
        {12, 3},
        {12, 4},
        {18, 6},
        {24, 8},
        {1000000000LL, 1},
        {1000000000LL, 1000},
        {1000000000LL, 1000000000LL},
    };

    auto [n, l] = rnd.any(shapes);
    int q = rnd.next(1, 60);

    println(n, l, q);

    vector<long long> pool;
    int smallLimit = static_cast<int>(min(n, 24LL));
    for (int i = 1; i <= smallLimit; ++i) {
        pool.push_back(i);
    }
    if (n > 24) {
        vector<long long> special = {
            n,
            max(1LL, n - 1),
            l,
            min(n, l + 1),
            max(1LL, n / 2),
            min(n, n / 2 + l),
        };
        for (long long x : special) {
            if (find(pool.begin(), pool.end(), x) == pool.end()) {
                pool.push_back(x);
            }
        }
    }

    vector<long long> active;
    for (int i = 0; i < q; ++i) {
        bool doRemove = !active.empty() && rnd.next(100) < 35;
        if (doRemove) {
            int index = rnd.next(static_cast<int>(active.size()));
            long long x = active[index];
            println(2, x);
            active.erase(active.begin() + index);
            continue;
        }

        long long x;
        bool replaceExisting = !active.empty() && rnd.next(100) < 25;
        if (replaceExisting) {
            x = rnd.any(active);
        } else {
            x = rnd.any(pool);
            if (find(active.begin(), active.end(), x) == active.end()) {
                active.push_back(x);
            }
        }

        long long t;
        int flavorMode = rnd.next(4);
        if (flavorMode == 0) {
            t = 1;
        } else if (flavorMode == 1) {
            t = rnd.next(1, 20);
        } else if (flavorMode == 2) {
            t = rnd.next(999999980LL, 1000000000LL);
        } else {
            t = rnd.next(1LL, 1000000000LL);
        }
        println(1, x, t);
    }

    return 0;
}
