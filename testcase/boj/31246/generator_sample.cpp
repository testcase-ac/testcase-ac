#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(30, 120) : rnd.next(1, 12));
    int k = rnd.next(1, n);

    vector<pair<long long, long long>> bids;
    bids.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            long long b = rnd.next(1, 1000);
            long long a = rnd.next(b, min(1000000000LL, b + 1000));
            bids.push_back({a, b});
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(1, 1000000000);
            bids.push_back({x, x});
        }
    } else if (mode == 2) {
        long long target = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            long long gap = max(0LL, target + rnd.next(-3, 3));
            long long a = rnd.next(1LL, 1000000000LL - gap);
            bids.push_back({a, a + gap});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(1, 20);
            long long b = rnd.next(999999980, 1000000000);
            bids.push_back({a, b});
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            long long a = rnd.next(999999980, 1000000000);
            long long b = rnd.next(1, 1000000000);
            bids.push_back({a, b});
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int pattern = rnd.next(0, 3);
            long long a, b;
            if (pattern == 0) {
                b = rnd.next(1, 1000000);
                a = rnd.next(b, min(1000000000LL, b + 1000000));
            } else if (pattern == 1) {
                a = rnd.next(1, 1000000000);
                b = a;
            } else if (pattern == 2) {
                long long gap = rnd.next(1, 1000000);
                a = rnd.next(1LL, 1000000000LL - gap);
                b = a + gap;
            } else {
                a = rnd.next(1, 1000000000);
                b = rnd.next(1, 1000000000);
            }
            bids.push_back({a, b});
        }
        shuffle(bids.begin(), bids.end());
    }

    println(n, k);
    for (auto [a, b] : bids) {
        println(a, b);
    }

    return 0;
}
