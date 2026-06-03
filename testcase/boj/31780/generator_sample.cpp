#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int x = 0;
    int m = 0;

    if (mode == 0) {
        x = rnd.next(0, 3);
        m = rnd.next(0, 3);
    } else if (mode == 1) {
        x = rnd.next(0, 100000000);
        m = 0;
    } else if (mode == 2) {
        x = rnd.next(0, 100000000);
        m = 20;
    } else if (mode == 3) {
        x = rnd.next(99999990, 100000000);
        m = rnd.next(0, 20);
    } else if (mode == 4) {
        x = 2 * rnd.next(0, 50000000);
        m = rnd.next(1, 20);
    } else {
        x = 2 * rnd.next(0, 49999999) + 1;
        m = rnd.next(1, 20);
    }

    println(x, m);
    return 0;
}
