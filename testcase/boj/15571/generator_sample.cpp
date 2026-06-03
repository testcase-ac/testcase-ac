#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(8);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 5);
        m = rnd.next(1, 20);
    } else if (mode == 1) {
        n = rnd.next(1, 30);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(2, 80);
        m = rnd.next(std::max(1, n - 3), n + 3);
    } else if (mode == 3) {
        n = rnd.next(1, 1000);
        m = rnd.next(1, std::min(1000000, n * 20));
    } else if (mode == 4) {
        n = rnd.next(900, 1000);
        m = rnd.next(1, 5000);
    } else if (mode == 5) {
        n = rnd.next(1, 20);
        m = rnd.next(999000, 1000000);
    } else if (mode == 6) {
        n = rnd.next(900, 1000);
        m = rnd.next(900000, 1000000);
    } else {
        n = rnd.next(1, 1000);
        m = rnd.next(1, 1000000);
    }

    println(n, m);
    return 0;
}
