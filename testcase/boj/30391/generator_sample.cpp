#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int k;

    if (mode == 0) {
        n = 3;
        k = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        k = 2;
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        k = n - 1;
    } else if (mode == 3) {
        n = rnd.next(4, 25);
        k = rnd.next(n / 2, n - 1);
    } else if (mode == 4) {
        n = rnd.next(4, 30);
        k = rnd.next(2, n - 2);
    } else if (mode == 5) {
        n = rnd.next(50, 200);
        k = rnd.next(2, n - 1);
    } else {
        n = rnd.next(290000, 300000);
        k = rnd.next(2, n - 1);
    }

    println(n, k);
    return 0;
}
