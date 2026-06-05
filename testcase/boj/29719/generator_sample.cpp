#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX = 1000000;
    int n;
    int m;

    int mode = rnd.next(0, 7);
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, MAX);
    } else if (mode == 1) {
        n = rnd.next(1, MAX);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(1, 10);
        m = rnd.next(1, 10);
    } else if (mode == 3) {
        n = rnd.next(1, 30);
        m = rnd.next(2, 30);
    } else if (mode == 4) {
        n = rnd.next(MAX - 1000, MAX);
        m = rnd.next(1, 20);
    } else if (mode == 5) {
        n = rnd.next(1, 20);
        m = rnd.next(MAX - 1000, MAX);
    } else if (mode == 6) {
        n = rnd.next(MAX - 1000, MAX);
        m = rnd.next(MAX - 1000, MAX);
    } else {
        n = rnd.next(1, MAX);
        m = rnd.next(1, MAX);
    }

    println(n, m);
    return 0;
}
