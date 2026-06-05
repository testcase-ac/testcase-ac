#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;

    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 999;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
    } else if (mode == 3) {
        n = rnd.next(11, 99);
    } else if (mode == 4) {
        n = rnd.next(100, 250);
    } else if (mode == 5) {
        n = rnd.next(251, 750);
    } else if (mode == 6) {
        n = rnd.next(751, 998);
    } else {
        n = rnd.next(1, 999);
    }

    println(n);
    return 0;
}
