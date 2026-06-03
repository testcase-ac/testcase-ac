#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;

    if (mode == 0) {
        n = rnd.next(3, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 1000);
    } else if (mode == 4) {
        n = rnd.next(4500, 5000);
    } else if (mode == 5) {
        n = 3 + 2 * rnd.next(0, 2498);
    } else {
        n = 4 + 2 * rnd.next(0, 2498);
    }

    println(n);
    return 0;
}
