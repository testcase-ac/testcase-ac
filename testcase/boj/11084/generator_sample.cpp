#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int r;
    int c;
    int mode = rnd.next(0, 7);

    if (mode == 0) {
        r = rnd.next(1, 2);
        c = rnd.next(1, 20);
    } else if (mode == 1) {
        r = rnd.next(3, 8);
        c = rnd.next(3, 8);
    } else if (mode == 2) {
        r = rnd.next(2, 12);
        c = rnd.next(13, 40);
    } else if (mode == 3) {
        int base = rnd.next(20, 80);
        r = base + rnd.next(-3, 3);
        c = base + rnd.next(-3, 3);
    } else if (mode == 4) {
        r = rnd.next(80, 180);
        c = rnd.next(3, 25);
    } else if (mode == 5) {
        r = rnd.next(181, 400);
        c = rnd.next(181, 400);
    } else if (mode == 6) {
        r = rnd.next(1, 400);
        c = rnd.next(1, 400);
    } else {
        r = rnd.next(360, 400);
        c = rnd.next(1, 40);
    }

    if (rnd.next(0, 1)) {
        int tmp = r;
        r = c;
        c = tmp;
    }

    println(r, c);
    return 0;
}
