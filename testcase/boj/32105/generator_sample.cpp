#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 200);
    } else if (mode == 3) {
        n = rnd.next(201, 2000);
    } else if (mode == 4) {
        n = rnd.next(90000, 100000);
    } else {
        n = rnd.next(1, 100000);
    }

    println(n);
    return 0;
}
