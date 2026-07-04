#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 6);
    } else if (mode == 6) {
        n = rnd.next(20, 40);
    } else {
        n = rnd.next(4, 18);
    }

    int k = rnd.next(0, 4);
    if (mode == 2 || mode == 3) {
        k = rnd.next(0, 2);
    }

    vector<int> a(n), b(n);

    if (mode == 0) {
        a[0] = rnd.any(vector<int>{-1000, -5, 0, 7, 1000});
        b[0] = rnd.next(-1000, 1000);
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            a[i] = 0;
            b[i] = rnd.next(-12, 12);
        }
        k = 2;
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = 0;
            b[i] = (i % 2 == 0 ? rnd.next(3, 20) : rnd.next(-20, -3));
        }
        if (rnd.next(2) == 0) {
            reverse(b.begin(), b.end());
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(-8, 8);
            b[i] = rnd.next(-8, 8);
        }
    } else if (mode == 4) {
        int high = rnd.next(20, 1000);
        int low = rnd.next(-1000, -20);
        for (int i = 0; i < n; ++i) {
            bool preferA = ((i / rnd.next(1, 3)) % 2 == 0);
            a[i] = preferA ? rnd.next(high / 2, high) : rnd.next(low, low / 2);
            b[i] = preferA ? rnd.next(low, low / 2) : rnd.next(high / 2, high);
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.any(vector<int>{-1000, -999, 0, 999, 1000});
            b[i] = rnd.any(vector<int>{-1000, -999, 0, 999, 1000});
        }
    } else {
        int lo = rnd.next(-1000, 0);
        int hi = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(lo, hi);
        }
    }

    println(n, k);
    println(a);
    println(b);

    return 0;
}
