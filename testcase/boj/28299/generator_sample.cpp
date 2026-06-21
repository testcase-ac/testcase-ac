#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MOD_MINUS_ONE = 998244352LL;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = 2;
        a = {rnd.next(1LL, 8LL), rnd.next(1LL, 8LL)};
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        a.assign(n, 1);
        int extra = rnd.next(0, 30);
        for (int i = 0; i < extra; ++i) ++a[rnd.next(0, n - 1)];
    } else if (mode == 2) {
        n = rnd.next(3, 16);
        a.assign(n, 1);
        int heavy = rnd.next(0, n - 1);
        a[heavy] = rnd.next(20LL, 120LL);
        for (int i = 0; i < n; ++i) {
            if (i != heavy && rnd.next(0, 2) == 0) a[i] += rnd.next(0LL, 5LL);
        }
    } else if (mode == 3) {
        n = rnd.next(4, 24);
        for (int i = 0; i < n; ++i) {
            long long value = (i % 2 == 0) ? rnd.next(1LL, 4LL)
                                           : rnd.next(8LL, 30LL);
            a.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(8, 60);
        long long value = rnd.next(1LL, 6LL);
        a.assign(n, value);
    } else if (mode == 5) {
        n = rnd.next(20, 80);
        a.assign(n, 1);
        int peaks = rnd.next(1, min(n, 8));
        for (int i = 0; i < peaks; ++i) {
            int pos = rnd.next(0, n - 1);
            a[pos] += rnd.any(vector<long long>{7, 31, 127, 255, 1024});
        }
    } else {
        n = rnd.next(2, 8);
        a.assign(n, 1);
        long long remaining = MOD_MINUS_ONE - n;
        int big = rnd.next(0, n - 1);
        a[big] += remaining;
    }

    if (rnd.next(0, 1) == 0) {
        reverse(a.begin(), a.end());
    } else {
        shuffle(a.begin(), a.end());
    }

    println(n);
    println(a);

    return 0;
}
