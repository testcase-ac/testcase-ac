#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = 1;
    int m = 1;
    int mode = rnd.next(8);

    if (mode == 0) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 10);
    } else if (mode == 1) {
        int total = rnd.next(9, 24);
        n = rnd.next(1, total - 1);
        m = total - n;
    } else if (mode == 2) {
        int base = rnd.next(2, 120);
        n = base;
        m = base + rnd.next(-1, 1);
        if (m < 1) m = 1;
    } else if (mode == 3) {
        n = rnd.next(1, 12);
        m = rnd.next(200, 10000);
    } else if (mode == 4) {
        n = rnd.next(200, 10000);
        m = rnd.next(1, 12);
    } else if (mode == 5) {
        n = rnd.next(9000, 10000);
        m = rnd.next(9000, 10000);
    } else if (mode == 6) {
        int total = rnd.next(100, 20000);
        n = rnd.next(1, 10000);
        m = total - n;
        if (m < 1) m = 1;
        if (m > 10000) m = 10000;
    } else {
        n = rnd.next(1, 10000);
        m = rnd.next(1, 10000);
    }

    println(n, m);
    return 0;
}
