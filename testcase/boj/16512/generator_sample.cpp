#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomValue(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 30);
    int k;
    vector<long long> a(n);

    if (mode == 0) {
        k = rnd.next(1, n);
        for (long long& x : a) {
            x = -randomValue(1, 100);
        }
    } else if (mode == 1) {
        k = rnd.next(1, n);
        long long high = randomValue(5, 80);
        for (int i = 0; i < n; ++i) {
            long long mag = randomValue(1, high);
            a[i] = (i % 2 == 0 ? mag : -mag);
        }
        if (rnd.next(0, 1)) {
            shuffle(a.begin(), a.end());
        }
    } else if (mode == 2) {
        k = rnd.next(1, min(n, 8));
        for (long long& x : a) {
            x = -randomValue(1, 40);
        }
        int blocks = rnd.next(1, min(n, 6));
        for (int b = 0; b < blocks; ++b) {
            int l = rnd.next(0, n - 1);
            int r = rnd.next(l, min(n - 1, l + rnd.next(0, 4)));
            for (int i = l; i <= r; ++i) {
                a[i] = randomValue(1, 60);
            }
        }
    } else if (mode == 3) {
        k = n;
        for (long long& x : a) {
            x = randomValue(-20, 20);
        }
    } else if (mode == 4) {
        k = rnd.next(1, n);
        vector<long long> choices = {-1000000000LL, -1LL, 0LL, 1LL, 1000000000LL};
        for (long long& x : a) {
            x = rnd.any(choices);
        }
    } else if (mode == 5) {
        k = rnd.next(1, n);
        long long value = randomValue(-10, 10);
        for (long long& x : a) {
            x = rnd.next(0, 3) == 0 ? 0 : value;
        }
    } else {
        k = rnd.next(max(1, n - 5), n);
        for (long long& x : a) {
            x = randomValue(-100, 100);
        }
    }

    println(n, k);
    println(a);

    return 0;
}
