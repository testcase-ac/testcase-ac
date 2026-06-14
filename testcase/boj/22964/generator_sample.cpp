#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxValue = 200000;
    int mode = rnd.next(0, 8);

    int n;
    int k;
    int x;

    if (mode == 0) {
        n = 1;
        k = 1;
        x = rnd.next(1, 5);
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        k = 1;
        x = rnd.next(1, 20);
    } else if (mode == 2) {
        n = rnd.next(2, 30);
        k = n;
        x = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(2, 60);
        k = rnd.next(1, n);
        x = 1;
    } else if (mode == 4) {
        n = rnd.next(2, 80);
        k = rnd.next(1, n);
        x = rnd.next(2, 200);
    } else if (mode == 5) {
        n = rnd.next(1000, maxValue);
        k = rnd.next(1, n);
        x = rnd.next(1, maxValue);
    } else if (mode == 6) {
        n = maxValue;
        k = rnd.next(1, n);
        x = rnd.next(1, maxValue);
    } else {
        n = rnd.next(1, maxValue);
        k = rnd.next(1, n);
        x = maxValue;
    }

    println(n, k, x);
    return 0;
}
