#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 12);
        k = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 20);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 9);
        k = rnd.next(n + 1, 10);
    } else if (mode == 3) {
        k = rnd.next(2, 10);
        n = k * rnd.next(1, 8);
    } else if (mode == 4) {
        k = rnd.next(2, 10);
        n = k * rnd.next(1, 8) - 1;
        if (n < 1) n = 1;
    } else if (mode == 5) {
        k = rnd.next(2, 10);
        n = k * rnd.next(1, 8) + 1;
    } else {
        n = rnd.next(1, 100000);
        k = rnd.next(0, 10);
    }

    println(n, k);
    return 0;
}
