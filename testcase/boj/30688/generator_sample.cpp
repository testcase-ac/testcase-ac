#include "testlib.h"

int evenInRange(int lo, int hi) {
    if (lo % 2 == 1) ++lo;
    if (hi % 2 == 1) --hi;
    ensure(lo <= hi);
    return lo + 2 * rnd.next((hi - lo) / 2 + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int k;

    if (mode == 0) {
        k = evenInRange(2, 20);
        n = rnd.next(k, k + 20);
    } else if (mode == 1) {
        k = evenInRange(2, 60);
        n = k;
    } else if (mode == 2) {
        k = evenInRange(2, 80);
        int offset = rnd.next(0, 2 * k + 10);
        n = k + offset;
    } else if (mode == 3) {
        k = evenInRange(2, 200);
        int block = rnd.next(1, 8);
        n = k * block + rnd.next(0, k);
    } else if (mode == 4) {
        k = evenInRange(1000, 20000);
        n = rnd.next(k, k + 20000);
    } else {
        n = rnd.next(2, 1000000);
        k = evenInRange(2, n);
    }

    println(n, k);
    return 0;
}
