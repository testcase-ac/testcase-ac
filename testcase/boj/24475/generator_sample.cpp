#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    long long m;
    vector<long long> a, b;

    if (mode == 0) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 1000000000);
    } else if (mode == 3) {
        n = rnd.next(2, 12);
        m = rnd.next(1, 30);
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        m = rnd.next(900000000, 1000000000);
    } else {
        n = rnd.next(1, 15);
        m = rnd.next(1, 50);
    }

    a.resize(n);
    b.resize(n);

    if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            long long x = rnd.next(1, 1000000000);
            a[i] = x;
            b[i] = x;
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                a[i] = rnd.next(1, 20);
                b[i] = rnd.next(900000000, 1000000000);
            } else {
                a[i] = rnd.next(900000000, 1000000000);
                b[i] = rnd.next(1, 20);
            }
        }
    } else {
        int valueMode = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            if (valueMode == 0) {
                a[i] = rnd.next(1, 20);
                b[i] = rnd.next(1, 20);
            } else if (valueMode == 1) {
                a[i] = rnd.next(1, 1000000);
                b[i] = rnd.next(1, 1000000);
            } else if (valueMode == 2) {
                a[i] = rnd.next(1, 1000000000);
                b[i] = rnd.next(1, 1000000000);
            } else {
                long long base = rnd.next(1, 1000);
                a[i] = base;
                b[i] = max(1LL, base + rnd.next(-5, 5));
            }
        }
    }

    if (rnd.next(0, 4) == 0) {
        shuffle(a.begin(), a.end());
        shuffle(b.begin(), b.end());
    }

    println(n, m);
    println(a);
    println(b);

    return 0;
}
