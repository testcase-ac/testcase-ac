#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int p;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(0, n);
        p = rnd.next(n, std::min(12, 100));
    } else if (mode == 1) {
        n = rnd.next(1, 100);
        m = 0;
        p = rnd.next(n, 100);
    } else if (mode == 2) {
        n = rnd.next(1, 100);
        m = n;
        p = rnd.next(n, 100);
    } else if (mode == 3) {
        n = rnd.next(1, 100);
        m = rnd.next(0, n);
        p = n;
    } else if (mode == 4) {
        n = rnd.next(1, 100);
        m = rnd.next(0, n);
        p = 100;
    } else {
        n = rnd.next(1, 100);
        m = rnd.next(0, n);
        p = rnd.next(n, 100);
    }

    println(n, m, p);
    return 0;
}
