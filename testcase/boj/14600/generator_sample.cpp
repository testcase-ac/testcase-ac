#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int k = (mode == 0 || mode == 1) ? 1 : 2;
    int n = 1 << k;
    int x;
    int y;

    if (mode == 0) {
        x = rnd.next(1, n);
        y = rnd.next(1, n);
    } else if (mode == 1) {
        x = rnd.next(0, 1) ? 1 : n;
        y = rnd.next(0, 1) ? 1 : n;
    } else if (mode == 2) {
        x = rnd.next(1, n);
        y = rnd.next(1, n);
    } else if (mode == 3) {
        x = rnd.next(0, 1) ? 1 : n;
        y = rnd.next(0, 1) ? 1 : n;
    } else if (mode == 4) {
        x = rnd.next(2, n - 1);
        y = rnd.next(2, n - 1);
    } else {
        int quadrant = rnd.next(0, 3);
        x = (quadrant % 2) * 2 + rnd.next(1, 2);
        y = (quadrant / 2) * 2 + rnd.next(1, 2);
    }

    println(k);
    println(x, y);

    return 0;
}
