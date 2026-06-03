#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(2, 5);
        k = rnd.next(1, n - 1);
    } else if (mode == 1) {
        n = rnd.next(6, 10);
        k = rnd.next(1, n - 1);
    } else if (mode == 2) {
        n = rnd.next(11, 16);
        k = rnd.next(1, n - 1);
    } else if (mode == 3) {
        n = rnd.next(2, 16);
        k = 1;
    } else if (mode == 4) {
        n = rnd.next(2, 16);
        k = n - 1;
    } else {
        n = rnd.next(3, 16);
        k = rnd.next(2, n - 1);
    }

    println(n, k);
    return 0;
}
