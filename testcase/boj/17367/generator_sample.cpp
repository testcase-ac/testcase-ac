#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 3;
    } else if (mode == 1) {
        n = rnd.next(4, 12);
    } else if (mode == 2) {
        n = rnd.next(13, 80);
    } else if (mode == 3) {
        n = rnd.next(81, 250);
    } else if (mode == 4) {
        n = rnd.next(251, 999);
    } else {
        n = 1000;
    }

    println(n);
    return 0;
}
