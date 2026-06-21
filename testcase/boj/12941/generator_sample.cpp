#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long bounded(long long value) {
    return max(1LL, min(1000000000LL, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    long long k;
    vector<long long> a;

    if (mode == 0) {
        k = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(1, 12));
        }
    } else if (mode == 1) {
        k = 2LL * rnd.next(0, 500000000) + 1;
        vector<long long> pool = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 15, 16, 31, 32, 63, 64};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 2) {
        k = 2LL * rnd.next(1, 500000000);
        for (int i = 0; i < n; ++i) {
            long long base = 1LL << rnd.next(0, 29);
            a.push_back(bounded(base + rnd.next(-2, 2)));
        }
    } else if (mode == 3) {
        k = rnd.next(1LL, 1000000000LL);
        n = rnd.next(12, 40);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                a.push_back(rnd.next(1, 20));
            } else if (i % 3 == 1) {
                a.push_back(2LL * rnd.next(1, 1000000));
            } else {
                a.push_back(2LL * rnd.next(1, 1000000) - 1);
            }
        }
    } else if (mode == 4) {
        k = rnd.any(vector<long long>{1, 2, 999999999LL, 1000000000LL});
        vector<long long> pool = {1, 2, 3, 4, 10, 11, 999999998LL, 999999999LL, 1000000000LL};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else {
        k = rnd.next(1LL, 1000000000LL);
        long long lo = rnd.next(1LL, 1000000000LL);
        long long hi = min(1000000000LL, lo + rnd.next(0, 1000));
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(lo, hi));
        }
    }

    shuffle(a.begin(), a.end());

    println(n, k);
    println(a);
    return 0;
}
