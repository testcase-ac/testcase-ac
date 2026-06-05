#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 12);
    } else if (mode == 1) {
        n = 2 * rnd.next(1, 2500);
    } else if (mode == 2) {
        n = 2 * rnd.next(0, 2499) + 1;
    } else if (mode == 3) {
        n = rnd.next(8, 40);
    } else if (mode == 4) {
        n = rnd.next(9500, 10000);
    } else {
        n = rnd.next(1, 10000);
    }

    println(n);
    return 0;
}
