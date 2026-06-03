#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int m;
    int k;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = 0;
        m = rnd.next(1, 500);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = rnd.next(1, 12);
        k = rnd.next(0, n * m);
    } else if (mode == 2) {
        n = rnd.next(1, 500);
        m = rnd.next(1, 500);
        k = rnd.next(0, 1) ? 0 : n * m;
    } else if (mode == 3) {
        n = rnd.next(1, 500);
        m = rnd.next(1, 500);
        k = n * m / 2 + rnd.next(-3, 3);
        if (k < 0) k = 0;
        if (k > n * m) k = n * m;
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        m = rnd.next(200, 500);
        k = rnd.next(0, n * m);
    } else if (mode == 5) {
        n = rnd.next(200, 500);
        m = rnd.next(1, 8);
        k = rnd.next(0, n * m);
    } else {
        n = rnd.next(450, 500);
        m = rnd.next(450, 500);
        k = rnd.next(0, n * m);
    }

    println(n, m, k);
    return 0;
}
