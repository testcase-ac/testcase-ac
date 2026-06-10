#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(0, 5);
    } else if (mode == 1) {
        n = rnd.next(6, 20);
    } else if (mode == 2) {
        n = rnd.next(21, 100);
    } else if (mode == 3) {
        n = rnd.next(101, 1000);
    } else if (mode == 4) {
        n = rnd.next(1001, 9999);
    } else {
        n = rnd.next(0, 1) == 0 ? 9999 : 10000;
    }

    println(n);
    return 0;
}
