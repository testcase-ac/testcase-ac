#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 7) {
        n = rnd.next(80, 200);
    } else {
        n = rnd.next(2, 40);
    }

    vector<long long> a(n, 1);
    const long long maxA = 1000000000LL;

    if (mode == 0) {
        a[0] = rnd.next(1, 4) == 1 ? maxA : rnd.next(1, 20);
    } else if (mode == 1) {
        long long cap = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            a[i] = min<long long>(cap, i + 1 + rnd.next(0, 2));
        }
    } else if (mode == 2) {
        long long cap = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            a[i] = min<long long>(cap, n - i + rnd.next(0, 2));
        }
    } else if (mode == 3) {
        int center = rnd.next(n);
        long long bonus = rnd.next(0, 5);
        for (int i = 0; i < n; ++i) {
            a[i] = max(1, center + 1 - abs(center - i)) + bonus + rnd.next(0, 2);
        }
    } else if (mode == 4) {
        long long low = rnd.next(1, 3);
        long long high = rnd.next(10, 80);
        for (int i = 0; i < n; ++i) {
            a[i] = (i % 2 == rnd.next(2)) ? low : high;
        }
    } else if (mode == 5) {
        long long lo = rnd.next(1, 15);
        long long hi = rnd.next(lo, lo + rnd.next(0, 80));
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
        }
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(10);
            if (pick == 0) {
                a[i] = maxA;
            } else if (pick <= 2) {
                a[i] = rnd.next(1000000LL, maxA);
            } else {
                a[i] = rnd.next(1, 30);
            }
        }
    } else {
        long long plateau = rnd.next(20, 200);
        for (int i = 0; i < n; ++i) {
            a[i] = plateau + rnd.next(-5, 5);
            if (rnd.next(12) == 0) {
                a[i] = 1;
            }
        }
    }

    println(n);
    println(a);
    return 0;
}
