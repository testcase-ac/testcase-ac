#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(7);
    int n;
    int k;
    int f;

    if (mode == 0) {
        n = 1;
        k = 0;
        f = 0;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
        k = rnd.next(0, n - 1);
        f = rnd.next(0, n - 1);
    } else if (mode == 2) {
        n = rnd.next(16, 20);
        k = rnd.next(0, n - 1);
        f = rnd.next(0, n - 1);
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        k = 0;
        f = rnd.next(0, n - 1);
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        k = n - 1;
        f = rnd.next(0, n - 1);
    } else if (mode == 5) {
        n = rnd.next(2, 20);
        k = rnd.next(0, n - 1);
        f = rnd.next(2) == 0 ? 0 : n - 1;
    } else {
        n = rnd.next(1, 20);
        k = rnd.next(0, n - 1);
        f = rnd.next(0, n - 1);
    }

    println(n);
    println(k);
    println(f);

    return 0;
}
