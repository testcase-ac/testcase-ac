#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    long long k;
    vector<int> v;

    if (mode == 0) {
        n = 2;
        k = rnd.next(1LL, 1000000000000LL);
        int base = rnd.next(1, 1000);
        v = {base, rnd.next(1, 1000000)};
    } else if (mode == 1) {
        n = rnd.next(3, 12);
        k = rnd.next(1LL, 1000000000000000000LL);
        int value = rnd.next(1, 1000000000);
        v.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        k = rnd.next(1LL, 1000000LL);
        int slow = rnd.next(1, 20);
        v.assign(n, slow);
        int fastCount = rnd.next(1, n - 1);
        for (int i = 0; i < fastCount; ++i) {
            v[i] = rnd.next(1000, 1000000000);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        k = rnd.next(1LL, 1000000000000000000LL);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) {
                v.push_back(1);
            } else if (i % 3 == 1) {
                v.push_back(1000000000);
            } else {
                v.push_back(rnd.next(1, 1000000000));
            }
        }
    } else if (mode == 4) {
        n = rnd.next(2, 40);
        k = rnd.next(1LL, 100000000000LL);
        int cur = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 10000);
            v.push_back(min(cur, 1000000000));
        }
    } else if (mode == 5) {
        n = rnd.next(2, 60);
        k = rnd.next(1LL, 1000000000000000000LL);
        int lo = rnd.next(1, 100000);
        int hi = rnd.next(lo, min(1000000000, lo + rnd.next(0, 1000000)));
        for (int i = 0; i < n; ++i) {
            v.push_back(rnd.next(lo, hi));
        }
    } else if (mode == 6) {
        n = rnd.next(50, 200);
        k = rnd.next(1LL, 1000000000000000000LL);
        for (int i = 0; i < n; ++i) {
            v.push_back(rnd.next(1, 1000000000));
        }
    } else {
        n = rnd.next(2, 25);
        long long totalSpeedHint = rnd.next(1LL, 1000000LL);
        k = totalSpeedHint * rnd.next(1LL, 1000000LL) + rnd.next(0LL, totalSpeedHint);
        for (int i = 0; i < n; ++i) {
            v.push_back(rnd.next(1, 1000000));
        }
    }

    shuffle(v.begin(), v.end());

    println(n, k);
    println(v);

    return 0;
}
