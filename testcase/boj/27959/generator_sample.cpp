#include "testlib.h"

int clampInt(int value, int lo, int hi) {
    if (value < lo) return lo;
    if (value > hi) return hi;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(1, 100);
    int m = rnd.next(1, 10000);

    if (mode == 0) {
        n = rnd.next(1, 100);
        m = clampInt(n * 100, 1, 10000);
    } else if (mode == 1) {
        n = rnd.next(1, 99);
        m = rnd.next(n * 100 + 1, 10000);
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        m = rnd.next(1, n * 100);
    } else if (mode == 3) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 400);
    } else if (mode == 4) {
        n = rnd.next(98, 100);
        m = rnd.next(9700, 10000);
    } else if (mode == 5) {
        n = rnd.next(1, 100);
        int delta = rnd.next(-250, 250);
        m = clampInt(n * 100 + delta, 1, 10000);
    }

    println(n, m);
    return 0;
}
