#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        k = n;
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        k = rnd.next(1, n);
    } else if (mode == 3) {
        n = rnd.next(21, 100);
        k = rnd.next(1, n);
    } else if (mode == 4) {
        n = rnd.next(101, 500);
        k = rnd.next(1, n);
    } else if (mode == 5) {
        n = rnd.next(1000, 5000);
        k = rnd.next(1, n);
    } else if (mode == 6) {
        n = 5000;
        k = rnd.next(1, n);
    } else {
        n = rnd.next(2, 5000);
        k = rnd.next(n - 1, n);
    }

    println(n, k);
    return 0;
}
