#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 7);
    } else if (mode == 1) {
        n = rnd.next(8, 10);
    } else if (mode == 2) {
        n = rnd.next(11, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 200);
    } else if (mode == 4) {
        n = rnd.next(201, 2000);
    } else if (mode == 5) {
        n = rnd.next(2001, 20000);
    } else if (mode == 6) {
        n = rnd.next(20001, 99999);
    } else {
        n = rnd.next(99990, 100000);
    }

    println(n);
    return 0;
}
