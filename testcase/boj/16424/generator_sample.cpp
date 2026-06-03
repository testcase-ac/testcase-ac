#include "testlib.h"

int makeEven(int x) {
    return x - (x % 2);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x;

    if (mode == 0) {
        x = 2 * rnd.next(0, 8);
    } else if (mode == 1) {
        int base = 10 * rnd.next(2, 12);
        int delta = 2 * rnd.next(-3, 3);
        x = base + delta;
    } else if (mode == 2) {
        x = 2 * rnd.next(0, 250);
    } else if (mode == 3) {
        x = 2 * rnd.next(250, 5000);
    } else if (mode == 4) {
        x = 2 * rnd.next(5000, 50000);
    } else {
        x = 1000000 - 2 * rnd.next(0, 5000);
    }

    x = makeEven(x);
    if (x < 0) x = 0;
    if (x > 1000000) x = 1000000;

    println(x);
    return 0;
}
