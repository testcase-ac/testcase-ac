#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

using int64 = long long;

const int64 LIMIT = 1000000000000LL;

int64 excessSum(const vector<int64>& a, int64 x) {
    int64 total = 0;
    for (int64 value : a) {
        if (value > x) {
            total += value - x;
            if (total > LIMIT) {
                return LIMIT;
            }
        }
    }
    return total;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 35);
    vector<int64> a;

    if (mode == 0) {
        n = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(vector<int64>{0, 1, 2, LIMIT - 1, LIMIT}));
        }
    } else if (mode == 1) {
        int64 value = rnd.next(0LL, LIMIT);
        a.assign(n, value);
    } else if (mode == 2) {
        int64 base = rnd.next(0LL, 1000LL);
        int64 step = rnd.next(0LL, 100LL);
        for (int i = 0; i < n; ++i) {
            a.push_back(min(LIMIT, base + step * i));
        }
    } else if (mode == 3) {
        int64 high = rnd.next(max(0LL, LIMIT - 1000), LIMIT);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(max(0LL, high - 5000), high));
        }
    } else if (mode == 4) {
        int64 low = rnd.next(0LL, 100LL);
        int64 high = rnd.next(max(low, LIMIT - 10000), LIMIT);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) ? rnd.next(low, min(LIMIT, low + 100)) : rnd.next(max(0LL, high - 100), high));
        }
    } else if (mode == 5) {
        n = rnd.next(20, 50);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0LL, 1000000LL));
        }
    } else {
        n = rnd.next(2, 35);
        int64 pivot = rnd.next(0LL, LIMIT);
        for (int i = 0; i < n; ++i) {
            int64 delta = rnd.next(0LL, 1000LL);
            if (rnd.next(0, 1)) {
                a.push_back(min(LIMIT, pivot + delta));
            } else {
                a.push_back(max(0LL, pivot - delta));
            }
        }
    }

    shuffle(a.begin(), a.end());

    int64 k;
    int kMode = rnd.next(0, 5);
    if (kMode == 0) {
        k = 0;
    } else if (kMode == 1) {
        k = LIMIT;
    } else if (kMode == 2) {
        k = rnd.next(0LL, 1000LL);
    } else {
        int64 x = rnd.any(a);
        int64 around = excessSum(a, x);
        int64 wiggle = rnd.next(0LL, 20LL);
        if (rnd.next(0, 1)) {
            k = min(LIMIT, around + wiggle);
        } else {
            k = max(0LL, around - wiggle);
        }
    }

    println(n, k);
    println(a);

    return 0;
}
