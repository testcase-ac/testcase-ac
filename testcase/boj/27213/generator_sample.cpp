#include "testlib.h"

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX = 100000000;
    int mode = rnd.next(0, 5);
    int m = 1;
    int n = 1;

    if (mode == 0) {
        m = 1;
        n = rnd.next(1, MAX);
    } else if (mode == 1) {
        m = rnd.next(1, MAX);
        n = 1;
    } else if (mode == 2) {
        m = rnd.next(2, 20);
        n = rnd.next(2, 20);
    } else if (mode == 3) {
        m = rnd.next(2, 1000);
        n = rnd.next(2, 1000);
    } else if (mode == 4) {
        m = rnd.next(MAX - 1000, MAX);
        n = rnd.next(2, 1000);
    } else {
        m = rnd.next(MAX - 1000, MAX);
        n = rnd.next(MAX - 1000, MAX);
    }

    if (rnd.next(0, 1)) {
        int tmp = m;
        m = n;
        n = tmp;
    }

    println(m);
    println(n);
    return 0;
}
