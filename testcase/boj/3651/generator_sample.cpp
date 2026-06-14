#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int64 MAX_M = 1000000000000000LL;

int64 chooseCapped(int n, int k) {
    k = min(k, n - k);
    __int128 value = 1;
    for (int i = 1; i <= k; ++i) {
        value = value * (n - k + i) / i;
        if (value > MAX_M) return MAX_M + 1;
    }
    return (int64)value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int64 m;

    if (mode == 0) {
        vector<int64> edges = {2, 3, 4, 15, MAX_M - 2, MAX_M - 1, MAX_M};
        m = rnd.any(edges);
    } else if (mode == 1) {
        m = rnd.next(2LL, 1000LL);
    } else if (mode == 2) {
        m = rnd.next(MAX_M - 1000000LL, MAX_M);
    } else if (mode == 3) {
        int64 n = rnd.next(2LL, 44721360LL);
        m = n * (n - 1) / 2;
    } else if (mode == 4) {
        vector<int64> powers;
        int64 base = rnd.next(2LL, 1000LL);
        int64 value = base;
        while (value <= MAX_M) {
            powers.push_back(value);
            if (value > MAX_M / base) break;
            value *= base;
        }
        m = rnd.any(powers);
    } else {
        vector<int64> candidates;
        for (int k = 3; k <= 20; ++k) {
            int lo = 2 * k;
            int hi = lo + rnd.next(0, 200);
            for (int n = lo; n <= hi; ++n) {
                int64 value = chooseCapped(n, k);
                if (2 <= value && value <= MAX_M) candidates.push_back(value);
            }
        }
        m = rnd.any(candidates);
    }

    println(m);
    return 0;
}
