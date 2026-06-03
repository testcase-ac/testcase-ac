#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(0, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 50);
    } else if (mode == 2) {
        int base = rnd.next(0, 333333) * 3;
        n = base + rnd.next(0, 2);
        if (n > 1000000) n -= 3;
    } else if (mode == 3) {
        n = rnd.next(950000, 1000000);
    } else if (mode == 4) {
        int k = rnd.next(1, 2000);
        n = 10007 * k + rnd.next(0, 20);
        if (n > 1000000) n = 1000000 - rnd.next(0, 20);
    } else {
        n = rnd.next(0, 1000000);
    }

    println(n);
    return 0;
}
