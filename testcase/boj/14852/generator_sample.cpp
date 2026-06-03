#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(9, 50);
    } else if (mode == 2) {
        n = rnd.next(51, 1000);
    } else if (mode == 3) {
        n = rnd.next(1001, 100000);
    } else if (mode == 4) {
        n = 1000000 - rnd.next(0, 999);
    } else {
        int base = rnd.next(1, 20);
        n = base * base + rnd.next(0, base);
    }

    println(n);
    return 0;
}
