#include "testlib.h"
#include <algorithm>

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int maxN = 1000000;
    int mode = rnd.next(0, 6);
    int n;
    int p;

    if (mode == 0) {
        n = rnd.next(2, 40);
        p = rnd.next(2, n);
    } else if (mode == 1) {
        n = rnd.next(2, 200000);
        p = 2;
    } else if (mode == 2) {
        n = rnd.next(2, 200000);
        p = n;
    } else if (mode == 3) {
        n = rnd.next(500000, maxN);
        int gap = rnd.next(0, std::min(1000, n - 2));
        p = n - gap;
    } else if (mode == 4) {
        n = rnd.next(1000, maxN);
        p = rnd.next(std::max(2, n / 2), n);
    } else if (mode == 5) {
        n = rnd.next(1000, maxN);
        p = rnd.next(2, std::max(2, n / 20));
    } else {
        n = rnd.next(2, maxN);
        p = rnd.next(2, n);
    }

    println(n, p);
    return 0;
}
