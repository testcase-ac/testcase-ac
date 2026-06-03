#include "testlib.h"

int halfUp(int value) {
    return (value + 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int x = rnd.next(1, 30);
    int y = rnd.next(1, 30);
    int z = rnd.next(1, 30);
    int xp = 0;
    int yp = 0;
    int zp = z;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        xp = x;
        yp = y;
    } else if (mode == 1 && x >= 2) {
        xp = rnd.next(halfUp(x), x - 1);
        yp = y;
    } else if (mode == 2) {
        xp = rnd.next(0, halfUp(x) - 1);
        yp = y;
    } else if (mode == 3 && y >= 2) {
        xp = rnd.next(0, x);
        yp = rnd.next(halfUp(y), y - 1);
    } else if (mode == 4) {
        xp = rnd.next(0, x);
        yp = rnd.next(0, halfUp(y) - 1);
    } else if (mode == 5) {
        xp = halfUp(x);
        yp = y;
    } else if (mode == 6) {
        xp = rnd.next(0, x);
        yp = halfUp(y) - 1;
    } else {
        xp = rnd.next(0, x);
        yp = rnd.next(0, y);
    }

    println(x, y, z);
    println(xp, yp, zp);

    return 0;
}
