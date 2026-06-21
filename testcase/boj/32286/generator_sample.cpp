#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int k = 1;
    int p = 1;
    int q = 1;
    int r = 1;
    int s = 1;
    int a1 = rnd.next(1, 10);

    if (mode == 0) {
        k = rnd.next(1, 8);
        p = rnd.next(1, 5);
        q = rnd.next(1, 5);
        r = rnd.next(1, 5);
        s = rnd.next(1, 5);
    } else if (mode == 1) {
        k = rnd.next(45, 50);
        p = rnd.next(1, 3);
        q = rnd.next(1, 3);
        r = rnd.next(1, 3);
        s = rnd.next(1, 3);
    } else if (mode == 2) {
        k = rnd.next(35, 50);
        p = rnd.next(90, 100);
        q = rnd.next(1, 10);
        r = rnd.next(1, 10);
        s = rnd.next(90, 100);
    } else if (mode == 3) {
        k = rnd.next(2, 20);
        p = rnd.next(1, 2);
        q = rnd.next(90, 100);
        r = rnd.next(1, 2);
        s = rnd.next(90, 100);
    } else if (mode == 4) {
        k = rnd.next(2, 20);
        p = rnd.next(90, 100);
        q = rnd.next(1, 2);
        r = rnd.next(90, 100);
        s = rnd.next(1, 2);
    } else if (mode == 5) {
        k = rnd.next(1, 50);
        p = rnd.next(1, 100);
        q = p;
        r = p;
        s = p;
    } else {
        k = rnd.next(1, 50);
        p = rnd.next(1, 100);
        q = rnd.next(1, 100);
        r = rnd.next(1, 100);
        s = rnd.next(1, 100);
    }

    println(k);
    println(p, q, r, s);
    println(a1);

    return 0;
}
