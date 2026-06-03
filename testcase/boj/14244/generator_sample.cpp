#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(3, 8);
        m = 2;
    } else if (mode == 1) {
        n = rnd.next(3, 8);
        m = n - 1;
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        m = rnd.next(2, n - 1);
    } else if (mode == 3) {
        n = rnd.next(13, 25);
        m = rnd.next(2, n - 1);
    } else if (mode == 4) {
        n = rnd.next(26, 50);
        m = rnd.next(2, n - 1);
    } else {
        n = 50;
        m = rnd.next(2, 49);
    }

    println(n, m);
    return 0;
}
