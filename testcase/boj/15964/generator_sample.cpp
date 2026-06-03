#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 1;
    int b = 1;
    int mode = rnd.next(6);

    if (mode == 0) {
        a = rnd.next(1, 1000);
        b = rnd.next(1, 1000);
    } else if (mode == 1) {
        a = rnd.next(99950, 100000);
        b = rnd.next(99950, 100000);
    } else if (mode == 2) {
        a = rnd.next(1, 100000);
        b = a;
    } else if (mode == 3) {
        a = rnd.next(1, 100000);
        b = rnd.next(1, 10);
    } else if (mode == 4) {
        a = rnd.next(1, 10);
        b = rnd.next(1, 100000);
    } else {
        a = rnd.next(1, 100000);
        b = rnd.next(1, 100000);
    }

    println(a, b);
    return 0;
}
