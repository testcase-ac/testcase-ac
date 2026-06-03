#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int s, k;

    if (mode == 0) {
        s = rnd.next(1, 100);
        k = 1;
    } else if (mode == 1) {
        s = rnd.next(1, 20);
        k = s;
    } else if (mode == 2) {
        k = rnd.next(2, 20);
        s = k;
    } else if (mode == 3) {
        k = rnd.next(2, 20);
        s = rnd.next(k, 100);
    } else if (mode == 4) {
        s = rnd.next(80, 100);
        k = rnd.next(1, 20);
    } else if (mode == 5) {
        k = rnd.next(2, 20);
        int q = rnd.next(1, 5);
        s = k * q + rnd.next(0, k - 1);
        if (s > 100) s = 100;
    } else {
        s = 100;
        k = rnd.next(1, 20);
    }

    println(s, k);
    return 0;
}
