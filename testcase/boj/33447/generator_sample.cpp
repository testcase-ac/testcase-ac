#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else if (mode == 2) {
        n = rnd.next(3, 10);
    } else if (mode == 3) {
        n = 2 * rnd.next(1, 25);
    } else if (mode == 4) {
        n = 2 * rnd.next(1, 25) + 1;
    } else if (mode == 5) {
        n = rnd.next(50, 200);
    } else if (mode == 6) {
        n = rnd.next(950, 1000);
    } else {
        n = rnd.next(1, 1000);
    }

    println(n);
    return 0;
}
