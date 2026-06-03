#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int m;

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = 1;
    } else if (mode == 2) {
        n = 8;
        m = rnd.next(1, 100000);
    } else if (mode == 3) {
        n = rnd.next(1, 8);
        m = rnd.next(99980, 100000);
    } else if (mode == 4) {
        n = rnd.next(1, 8);
        m = rnd.next(1, 20);
    } else if (mode == 5) {
        n = rnd.next(1, 8);
        m = rnd.next(1000, 100000);
    } else {
        n = rnd.next(1, 8);
        m = rnd.next(1, 100000);
    }

    println(n, m);
    return 0;
}
