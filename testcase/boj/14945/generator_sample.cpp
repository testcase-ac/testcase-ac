#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 40);
    } else if (mode == 2) {
        n = rnd.next(41, 100);
    } else {
        n = rnd.next(2, 100);
    }

    println(n);
    return 0;
}
