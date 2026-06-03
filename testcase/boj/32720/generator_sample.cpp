#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int n;
    int k;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(2, 30);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        k = rnd.next(2, 30);
        int q = rnd.next(2, 30);
        int r = rnd.next(1, k - 1);
        n = k * q + r;
    } else if (mode == 5) {
        n = rnd.next(maxN - 1000, maxN);
        k = rnd.next(1, 1000);
    } else if (mode == 6) {
        n = rnd.next(maxN - 1000, maxN);
        k = rnd.next(n - 1000, n);
    } else {
        n = rnd.next(31, maxN);
        k = rnd.next(1, n);
    }

    println(n, k);
    return 0;
}
