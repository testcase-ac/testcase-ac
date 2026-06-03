#include "testlib.h"

int randomWithParity(int lo, int hi, int parity) {
    if (lo % 2 != parity) ++lo;
    if (hi % 2 != parity) --hi;
    return lo + 2 * rnd.next((hi - lo) / 2 + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    if (mode == 0) {
        n = rnd.next(4, 8);
    } else if (mode == 1) {
        n = randomWithParity(4, 60, 0);
    } else if (mode == 2) {
        n = randomWithParity(5, 61, 1);
    } else if (mode == 3) {
        n = rnd.next(62, 200);
    } else if (mode == 4) {
        n = rnd.next(201, 800);
    } else {
        n = rnd.next(950, 1000);
    }

    println(n);
    return 0;
}
