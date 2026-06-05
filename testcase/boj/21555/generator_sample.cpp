#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    long long k;
    long long lo = 1, hi = 30;

    if (mode == 0) {
        n = rnd.next(1, 3);
        k = rnd.next(0, 3);
        hi = 8;
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        k = 0;
        hi = 50;
    } else if (mode == 2) {
        n = rnd.next(2, 12);
        k = rnd.next(1000000LL, 1000000000LL);
        hi = 100;
    } else if (mode == 3) {
        n = rnd.next(4, 20);
        k = rnd.next(1, 20);
        hi = 100;
    } else if (mode == 4) {
        n = rnd.next(3, 25);
        k = rnd.next(0, 100);
        lo = rnd.next(1LL, 20LL);
        hi = lo + rnd.next(0, 5);
    } else if (mode == 5) {
        n = rnd.next(10, 60);
        k = rnd.next(0LL, 1000000000LL);
        hi = 1000000000LL;
    } else {
        n = rnd.next(1, 200);
        k = rnd.next(0, 1000);
        hi = 1000;
    }

    vector<long long> a(n), b(n);
    if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long cheap = rnd.next(1, 20);
            long long expensive = rnd.next(cheap + 1, 100LL);
            if (i % 2 == 0) {
                a[i] = cheap;
                b[i] = expensive;
            } else {
                a[i] = expensive;
                b[i] = cheap;
            }
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
        if (rnd.next(0, 4) == 0) {
            int pos = rnd.next(0, n - 1);
            a[pos] = b[pos];
        }
    }

    println(n, k);
    println(a);
    println(b);

    return 0;
}
