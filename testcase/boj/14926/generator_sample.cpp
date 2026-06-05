#include "testlib.h"

int randomOdd(int lo, int hi) {
    int count = (hi - lo) / 2 + 1;
    return lo + 2 * rnd.next(count);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode == 1) {
        n = 499;
    } else if (mode == 2) {
        n = randomOdd(3, 21);
    } else if (mode == 3) {
        n = randomOdd(23, 99);
    } else if (mode == 4) {
        n = randomOdd(101, 499);
    } else {
        n = randomOdd(3, 499);
    }

    println(n);
    return 0;
}
