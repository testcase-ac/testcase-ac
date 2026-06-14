#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MAX_M = 1000000000000000000LL;
const int64 MAX_COST = 10000000000000000LL;

int64 boundedCost(int64 value) {
    return max<int64>(1, min<int64>(MAX_COST, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int64 m;
    vector<int64> costs;

    if (mode == 0) {
        n = rnd.next(1, 6);
        m = rnd.next(1LL, 30LL);
        for (int i = 0; i < n; ++i) {
            costs.push_back(rnd.next(1LL, 30LL));
        }
    } else if (mode == 1) {
        n = rnd.next(8, 20);
        int64 base = rnd.next(1LL, 5000LL);
        m = base * rnd.next(2, min(n, 8));
        for (int i = 0; i < n; ++i) {
            costs.push_back(base + rnd.next(-2LL, 2LL));
            costs.back() = boundedCost(costs.back());
        }
    } else if (mode == 2) {
        n = rnd.next(10, 28);
        m = rnd.next(1LL, 1000000LL);
        for (int i = 0; i < n; ++i) {
            int64 value = 1LL << rnd.next(0, 20);
            costs.push_back(boundedCost(value + rnd.next(0LL, value - 1)));
        }
    } else if (mode == 3) {
        n = rnd.next(5, 18);
        m = rnd.next(1LL, 1000LL);
        for (int i = 0; i < n; ++i) {
            costs.push_back(rnd.next(m + 1, min(MAX_COST, m + 1000000LL)));
        }
    } else if (mode == 4) {
        n = 40;
        m = rnd.next(MAX_M - 1000000000000000LL, MAX_M);
        int64 lo = MAX_COST - 1000000000000LL;
        for (int i = 0; i < n; ++i) {
            costs.push_back(rnd.next(lo, MAX_COST));
        }
    } else if (mode == 5) {
        n = rnd.next(20, 40);
        int64 small = rnd.next(1LL, 100LL);
        m = small * rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                costs.push_back(rnd.next(m + 1, min(MAX_COST, m + 1000)));
            } else {
                costs.push_back(rnd.next(1LL, small));
            }
        }
    } else {
        n = rnd.next(30, 40);
        m = rnd.next(1LL, MAX_M);
        for (int i = 0; i < n; ++i) {
            int64 bucket = rnd.next(0, 4);
            if (bucket == 0) {
                costs.push_back(rnd.next(1LL, 1000LL));
            } else if (bucket == 1) {
                costs.push_back(rnd.next(1000000LL, 1000000000LL));
            } else if (bucket == 2) {
                costs.push_back(rnd.next(1000000000000LL, MAX_COST));
            } else {
                costs.push_back(boundedCost(m / rnd.next(2, 20) + rnd.next(-1000LL, 1000LL)));
            }
        }
    }

    shuffle(costs.begin(), costs.end());

    println(n, m);
    println(costs);

    return 0;
}
