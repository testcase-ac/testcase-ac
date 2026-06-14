#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 30);
    } else if (mode == 2) {
        n = rnd.next(31, 120);
    } else if (mode == 3) {
        n = rnd.next(121, 299);
    } else {
        n = rnd.next(290, 300);
    }

    println(n);
    return 0;
}
