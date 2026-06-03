#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a;
    int b;
    int c;

    int mode = rnd.next(0, 5);
    if (mode == 0) {
        a = rnd.next(2, 8);
        b = rnd.next(2, 8);
        c = rnd.next(2, 8);
    } else if (mode == 1) {
        a = rnd.next(9990, 10000);
        b = rnd.next(9990, 10000);
        c = rnd.next(9990, 10000);
    } else if (mode == 2) {
        c = rnd.next(2, 100);
        a = c * rnd.next(1, 10000 / c);
        b = c * rnd.next(1, 10000 / c);
    } else if (mode == 3) {
        c = rnd.next(2, 10000);
        a = c;
        b = rnd.next(2, 10000);
    } else if (mode == 4) {
        c = rnd.next(2, 10000);
        a = rnd.next(2, c);
        b = rnd.next(2, c);
    } else {
        a = rnd.next(2, 10000);
        b = rnd.next(2, 10000);
        c = rnd.next(2, 10000);
    }

    println(a, b, c);
    return 0;
}
