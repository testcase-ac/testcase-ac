#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a, b;

    if (mode == 0) {
        a = rnd.next(1, 12);
        b = a;
    } else if (mode == 1) {
        a = rnd.next(1, 12);
        b = rnd.next(a, 60);
    } else if (mode == 2) {
        a = rnd.next(1, 100);
        b = rnd.next(90000, 100000);
    } else if (mode == 3) {
        b = rnd.next(99950, 100000);
        a = rnd.next(99900, b);
    } else if (mode == 4) {
        a = rnd.next(1, 100000);
        b = rnd.next(a, 100000);
    } else {
        b = rnd.next(2, 200);
        a = rnd.next(1, b);
    }

    println(a, b);
    return 0;
}
