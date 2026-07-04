#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<long long> a;

    if (mode == 0) {
        n = rnd.next(2, 8);
        long long value = rnd.next(1, 20);
        a.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 10);
        a.assign(n, rnd.next(1, 8));
        int dominant = rnd.next(n);
        long long sumOthers = 0;
        for (int i = 0; i < n; ++i) {
            if (i != dominant) {
                a[i] = rnd.next(1, 12);
                sumOthers += a[i];
            }
        }
        a[dominant] = sumOthers + rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        a.resize(n);
        long long cur = rnd.next(1, 4);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 6);
            a[i] = cur;
        }
    } else if (mode == 3) {
        n = rnd.next(4, 14);
        a.resize(n);
        long long high = rnd.next(20, 200);
        long long low = rnd.next(1, 9);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == 0) ? rnd.next(high / 2, high) : rnd.next(1LL, low);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 1000);
        }
    } else if (mode == 5) {
        n = rnd.next(2, 9);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            int exponent = rnd.next(0, 8);
            a[i] = 1LL << exponent;
        }
    } else if (mode == 6) {
        n = rnd.next(2, 30);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(999999900LL, 1000000000LL);
        }
    } else {
        n = rnd.next(2, 100);
        a.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.wnext(1000000000, -3) + 1LL;
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(a.begin(), a.end());
    } else if (rnd.next(0, 1)) {
        reverse(a.begin(), a.end());
    }

    println(n);
    println(a);
    return 0;
}
