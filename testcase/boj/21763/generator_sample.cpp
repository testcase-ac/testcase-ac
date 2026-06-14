#include "testlib.h"

#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = 1;
        k = rnd.next(0, 1);
    } else if (mode == 1) {
        n = 2;
        k = rnd.next(0, 4);
    } else if (mode == 2) {
        n = rnd.next(3, 4);
        k = rnd.next(0, n * n);
    } else if (mode == 3) {
        n = rnd.next(3, 20);
        k = rnd.next(0, n - 1);
    } else if (mode == 4) {
        n = rnd.next(3, 100);
        int boundary = n * n - n;
        k = std::max(0, boundary + rnd.next(-2, 2));
    } else if (mode == 5) {
        n = rnd.next(3, 100);
        k = n * n - rnd.next(0, std::min(n + 2, n * n));
    } else if (mode == 6) {
        n = rnd.next(5, 100);
        k = rnd.wnext(n * n + 1, 3);
    } else {
        n = rnd.next(1, 100);
        k = rnd.next(0, n * n);
    }

    println(n, k);
    return 0;
}
