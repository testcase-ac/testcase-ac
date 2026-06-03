#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 40);
        k = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        k = n;
    } else if (mode == 3) {
        n = rnd.next(2, 80);
        k = rnd.next(2, n);
    } else if (mode == 4) {
        n = rnd.next(81, 250);
        k = rnd.next(2, 10);
    } else if (mode == 5) {
        n = rnd.next(251, 500);
        k = rnd.next(2, 20);
    } else if (mode == 6) {
        n = rnd.next(100, 500);
        k = rnd.next(n / 2, n);
    } else {
        n = rnd.next(1, 500);
        k = rnd.next(1, n);
    }

    println(n, k);
    return 0;
}
