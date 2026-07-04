#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int k;
    if (mode == 0) {
        k = rnd.next(2, 12);
    } else if (mode == 1) {
        k = rnd.next(13, 80);
    } else if (mode == 2) {
        k = rnd.next(81, 250);
    } else if (mode == 3) {
        k = rnd.next(251, 499);
    } else {
        k = 500;
    }

    println(k);
    return 0;
}
