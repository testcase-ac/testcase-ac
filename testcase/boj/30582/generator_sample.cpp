#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int d = 1;
    int r = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        d = rnd.next(1, 6);
        r = rnd.next(1, 6);
    } else if (mode == 1) {
        d = rnd.next(45, 50);
        r = rnd.next(45, 50);
    } else if (mode == 2) {
        d = rnd.next(35, 50);
        r = rnd.next(1, 8);
    } else if (mode == 3) {
        d = rnd.next(1, 8);
        r = rnd.next(35, 50);
    } else if (mode == 4) {
        d = rnd.next(10, 30);
        r = rnd.next(10, 30);
    } else {
        d = rnd.next(1, 50);
        r = rnd.next(1, 50);
    }

    println(d, r);
    return 0;
}
