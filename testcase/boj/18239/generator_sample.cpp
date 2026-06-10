#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int k;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = 2;
        k = 1;
    } else if (mode == 1) {
        n = 3;
        k = rnd.next(1, 2);
    } else if (mode == 2) {
        n = rnd.next(4, 40);
        k = 1;
    } else if (mode == 3) {
        n = rnd.next(4, 40);
        k = n - 1;
    } else if (mode == 4) {
        n = rnd.next(4, 80);
        k = rnd.next(2, n - 2);
    } else if (mode == 5) {
        n = rnd.next(1000, 10000000);
        k = rnd.next(1, n - 1);
    } else {
        n = 10000000 - rnd.next(0, 1000);
        k = rnd.next(1, n - 1);
    }

    println(n, k);
    return 0;
}
