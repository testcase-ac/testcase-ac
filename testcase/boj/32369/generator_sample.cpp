#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 15);
    } else if (mode == 2) {
        n = rnd.next(16, 40);
    } else if (mode == 3) {
        n = rnd.next(41, 99);
    } else {
        n = 100;
    }

    int a;
    int b;
    int growthMode = rnd.next(0, 4);
    if (growthMode == 0) {
        a = rnd.next(1, 9);
        b = a + 1;
    } else if (growthMode == 1) {
        a = 1;
        b = rnd.next(2, 10);
    } else if (growthMode == 2) {
        b = 10;
        a = rnd.next(1, 9);
    } else {
        a = rnd.next(1, 9);
        b = rnd.next(a + 1, 10);
    }

    println(n, a, b);
    return 0;
}
