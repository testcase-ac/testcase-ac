#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MIN_X = -1000000000;
const int MAX_X = 1000000000;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 18);
    int k = rnd.next(1, 12);

    if (mode == 4) {
        n = rnd.next(20, 45);
        k = rnd.next(20, 60);
    } else if (mode == 5) {
        n = rnd.next(1, 8);
        k = rnd.next(1, 20);
    }

    vector<long long> a(n);
    if (mode == 0) {
        long long lo = rnd.next(-20, 5);
        long long hi = rnd.next(6, 30);
        for (long long& value : a) value = rnd.next(lo, hi);
    } else if (mode == 1) {
        long long start = rnd.next(-100, 100);
        long long step = rnd.next(0, 8);
        for (int i = 0; i < n; ++i) a[i] = start + step * i + rnd.next(-2, 2);
        shuffle(a.begin(), a.end());
    } else if (mode == 2) {
        vector<long long> pool = {-1000000000000000000LL, -999999999000000000LL,
                                  -1000000000LL, 0LL, 1000000000LL,
                                  999999999000000000LL, 1000000000000000000LL};
        for (long long& value : a) value = rnd.any(pool);
    } else if (mode == 3) {
        long long center = rnd.next(-1000000LL, 1000000LL);
        for (long long& value : a) value = center + rnd.next(-3, 3);
    } else {
        long long lo = rnd.next(-1000000000000LL, 0LL);
        long long hi = rnd.next(0LL, 1000000000000LL);
        for (long long& value : a) value = rnd.next(lo, hi);
    }

    println(n, k);
    println(a);

    for (int i = 0; i < k; ++i) {
        int l, r;
        if (mode == 0 && rnd.next(0, 2) == 0) {
            l = 1;
            r = n;
        } else if (mode == 1) {
            l = rnd.next(1, n);
            r = min(n, l + rnd.next(0, min(4, n - l)));
        } else if (mode == 5) {
            l = r = rnd.next(1, n);
        } else {
            l = rnd.next(1, n);
            r = rnd.next(l, n);
        }

        int x;
        if (mode == 2) {
            vector<int> shifts = {MIN_X, -1, 0, 1, MAX_X};
            x = rnd.any(shifts);
        } else if (mode == 3) {
            x = rnd.next(-5, 5);
        } else if (mode == 4) {
            x = rnd.next(-1000000, 1000000);
        } else {
            x = rnd.next(-1000, 1000);
        }

        println(l, r, x);
    }

    return 0;
}
