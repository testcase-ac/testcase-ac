#include "testlib.h"
#include <vector>
using namespace std;

int bounded(int value) {
    if (value < 1) return 1;
    if (value > 100) return 100;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int sizeMode = rnd.next(0, 5);
    int n;
    if (sizeMode == 0) {
        n = 1;
    } else if (sizeMode == 1) {
        n = rnd.next(2, 5);
    } else if (sizeMode == 2) {
        n = rnd.next(6, 20);
    } else if (sizeMode == 3) {
        n = rnd.next(21, 80);
    } else if (sizeMode == 4) {
        n = rnd.next(81, 160);
    } else {
        n = 1000;
    }

    int pattern = rnd.next(0, 5);
    vector<int> a(n), b(n);
    int lo = rnd.next(1, 90);
    int hi = rnd.next(lo, 100);

    for (int i = 0; i < n; ++i) {
        if (pattern == 0) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(a[i], 100);
        } else if (pattern == 1) {
            a[i] = rnd.next(lo, hi);
            b[i] = rnd.next(1, a[i]);
        } else if (pattern == 2) {
            a[i] = rnd.next(lo, hi);
            int delta = rnd.next(-5, 5);
            b[i] = bounded(a[i] + delta);
        } else if (pattern == 3) {
            a[i] = (i % 2 == 0 ? 1 : 100);
            b[i] = rnd.next(1, 100);
        } else if (pattern == 4) {
            a[i] = rnd.next(1, 100);
            b[i] = (i % 3 == 0 ? a[i] : rnd.next(1, 100));
        } else {
            a[i] = rnd.next(1, 100);
            b[i] = rnd.next(1, 100);
        }
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
