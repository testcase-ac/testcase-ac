#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 8);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 10000);
    } else if (mode == 2) {
        n = rnd.next(80, 100);
        m = rnd.next(1, 25);
    } else if (mode == 3) {
        n = rnd.next(2, 100);
        m = rnd.next(1, n - 1);
    } else if (mode == 4) {
        n = rnd.next(1, 100);
        int lo = std::max(1, n - 5);
        int hi = std::min(10000, n + 5);
        m = rnd.next(lo, hi);
    } else if (mode == 5) {
        n = rnd.next(10, 100);
        m = rnd.next(500, 2000);
    } else if (mode == 6) {
        n = rnd.next(2, 30);
        m = rnd.next(1990, 2010);
    } else if (mode == 7) {
        n = rnd.next(1, 100);
        m = rnd.next(9000, 10000);
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(1, 10000);
    }

    println(n, m);
    return 0;
}
