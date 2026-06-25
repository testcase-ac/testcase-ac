#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 2;
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = 20;
        k = rnd.next(1, n);
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        k = 1;
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        k = n;
    } else if (mode == 4) {
        n = rnd.next(2, 20);
        k = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(2, 8);
        k = rnd.next(1, n);
    } else if (mode == 6) {
        n = rnd.next(10, 20);
        k = rnd.next(1, 3);
    } else {
        n = rnd.next(10, 20);
        k = rnd.next(n - 2, n);
    }

    println(n, k);
    return 0;
}
