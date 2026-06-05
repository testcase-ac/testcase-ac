#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 14);
    } else {
        n = 15;
    }

    println(n);
    return 0;
}
