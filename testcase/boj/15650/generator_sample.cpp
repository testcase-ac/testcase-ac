#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int m;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = 1;
    } else if (mode == 1) {
        n = rnd.next(1, 8);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(1, n - 1);
    } else if (mode == 3) {
        n = 8;
        m = rnd.next(1, 8);
    } else if (mode == 4) {
        n = rnd.next(1, 4);
        m = rnd.next(1, n);
    } else {
        m = rnd.next(1, 8);
        n = rnd.next(m, 8);
    }

    println(n, m);
    return 0;
}
