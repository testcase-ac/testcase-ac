#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int h1, h2, h3;
    long long n;

    if (mode == 0) {
        h1 = h2 = h3 = rnd.next(1, 100);
        n = rnd.next(1, 20);
    } else if (mode == 1) {
        h1 = rnd.next(1, 98);
        h2 = rnd.next(h1 + 1, 99);
        h3 = rnd.next(h2 + 1, 100);
        n = rnd.next(1, 50);
    } else if (mode == 2) {
        h1 = rnd.next(1, 100);
        h2 = rnd.next(h1, 100);
        h3 = 100;
        n = rnd.next(1, 1000);
    } else if (mode == 3) {
        h1 = 1;
        h2 = rnd.next(1, 100);
        h3 = rnd.next(h2, 100);
        n = rnd.next(1, 1000);
    } else if (mode == 4) {
        h1 = rnd.next(1, 100);
        h2 = rnd.next(h1, 100);
        h3 = rnd.next(h2, 100);
        n = 2LL * rnd.next(0, 500000000) + 1;
    } else if (mode == 5) {
        h1 = rnd.next(1, 100);
        h2 = rnd.next(h1, 100);
        h3 = rnd.next(h2, 100);
        n = 2LL * rnd.next(1, 500000000);
    } else if (mode == 6) {
        h1 = rnd.next(1, 100);
        h2 = rnd.next(h1, 100);
        h3 = rnd.next(h2, 100);
        n = 1000000000000LL - rnd.next(0, 1000);
    } else {
        h1 = rnd.next(1, 100);
        h2 = rnd.next(h1, 100);
        h3 = rnd.next(h2, 100);
        n = rnd.next(1LL, 1000000000000LL);
    }

    println(h1, h2, h3);
    println(n);
    return 0;
}
