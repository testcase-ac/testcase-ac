#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(6, 10);
    } else if (mode == 2) {
        n = rnd.next(50, 55);
    } else if (mode == 3) {
        n = rnd.next(1, 55);
    } else if (mode == 4) {
        n = rnd.wnext(55, -3) + 1;
    } else {
        n = rnd.wnext(55, 3) + 1;
    }

    println(n);
    return 0;
}
