#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n;
    if (mode == 0) {
        n = rnd.next(0, 1);
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(6, 12);
    } else if (mode == 3) {
        n = rnd.next(13, 19);
    } else {
        n = 20;
    }

    println(n);
    return 0;
}
