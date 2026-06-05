#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int w = 1;
    int h = 1;
    int d = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        d = rnd.next(1, 20);
        w = rnd.next(2 * d, 2 * d + 60);
        h = rnd.next(2 * d, 2 * d + 60);
    } else if (mode == 1) {
        d = rnd.next(1, 99);
        w = rnd.next(1, 2 * d - 1);
        h = rnd.next(1, 999);
    } else if (mode == 2) {
        d = rnd.next(1, 99);
        w = rnd.next(1, 999);
        h = rnd.next(1, 2 * d - 1);
    } else if (mode == 3) {
        d = rnd.next(1, 99);
        w = 2 * d;
        h = rnd.next(1, 999);
    } else if (mode == 4) {
        d = rnd.next(1, 99);
        w = rnd.next(1, 999);
        h = 2 * d;
    } else {
        d = rnd.next(1, 99);
        w = rnd.next(800, 999);
        h = rnd.next(800, 999);
    }

    println(w, h, d);
    return 0;
}
