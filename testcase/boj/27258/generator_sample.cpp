#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int p;
    int q;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1, 6);
        p = rnd.next(2, 12);
        q = rnd.next(1, p - 1);
    } else if (mode == 1) {
        n = rnd.next(90, 100);
        p = rnd.next(90, 100);
        q = rnd.next(1, p - 1);
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        p = rnd.next(2, 100);
        q = p - 1;
    } else if (mode == 3) {
        n = rnd.next(1, 100);
        p = rnd.next(2, 100);
        q = 1;
    } else if (mode == 4) {
        n = rnd.next(1, 100);
        q = rnd.next(1, 10);
        p = rnd.next(q + 1, 100);
    } else {
        n = rnd.next(1, 100);
        p = rnd.next(2, 100);
        q = rnd.next(1, p - 1);
    }

    println(n, p, q);
    return 0;
}
