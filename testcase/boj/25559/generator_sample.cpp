#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int n;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 15);
    } else if (mode == 2) {
        n = 2 * rnd.next(1, 15) + 1;
    } else if (mode == 3) {
        n = rnd.next(2, 60);
    } else if (mode == 4) {
        n = maxN - rnd.next(0, 20);
    } else if (mode == 5) {
        int exponent = rnd.next(1, 19);
        n = 1 << exponent;
        if (rnd.next(0, 1) == 1 && n < maxN) {
            ++n;
        }
    } else {
        n = rnd.next(1, maxN);
    }

    println(n);
    return 0;
}
