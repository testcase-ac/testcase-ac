#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = 2;
    } else if (mode == 1) {
        n = 3;
    } else if (mode == 2) {
        n = rnd.next(4, 10);
    } else if (mode == 3) {
        n = rnd.next(11, 50);
    } else if (mode == 4) {
        n = rnd.next(51, 200);
    } else {
        n = rnd.next(900, 1000);
    }

    println(n);
    return 0;
}
