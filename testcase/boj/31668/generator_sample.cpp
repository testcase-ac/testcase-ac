#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n, m, k;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 1000);
        k = rnd.next(1, 1000);
    } else if (mode == 1) {
        n = rnd.next(1, 1000);
        m = n;
        k = rnd.next(1, 1000);
    } else if (mode == 2) {
        int q = rnd.next(1, 1000);
        n = rnd.next(1, 1000 / q);
        m = n * q;
        k = rnd.next(0, 1) == 0 ? 1 : 1000;
    } else if (mode == 3) {
        n = rnd.next(1, 31);
        int q = rnd.next(1, 1000 / n);
        m = n * q;
        k = rnd.next(1, 31);
    } else if (mode == 4) {
        n = rnd.next(32, 1000);
        int q = rnd.next(1, 1000 / n);
        m = n * q;
        k = rnd.next(970, 1000);
    } else {
        int q = rnd.next(1, 1000);
        n = 1000 / q;
        m = n * q;
        k = rnd.next(1, 1000);
    }

    println(n);
    println(m);
    println(k);

    return 0;
}
