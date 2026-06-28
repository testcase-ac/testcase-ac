#include "testlib.h"

#include <algorithm>
#include <vector>

int maxInversions(int n) {
    return n * (n - 1) / 2;
}

int clampK(int n, int k) {
    return std::max(0, std::min(k, maxInversions(n)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(0, maxInversions(n));
    } else if (mode == 1) {
        n = rnd.next(1, 500);
        k = rnd.any(std::vector<int>{0, maxInversions(n)});
    } else if (mode == 2) {
        n = rnd.next(2, 500);
        int edge = rnd.any(std::vector<int>{0, maxInversions(n)});
        int delta = rnd.next(0, std::min(20, maxInversions(n)));
        k = edge == 0 ? delta : edge - delta;
    } else if (mode == 3) {
        n = rnd.next(1, 32);
        int center = maxInversions(n) / 2;
        k = clampK(n, center + rnd.next(-20, 20));
    } else if (mode == 4) {
        n = rnd.next(1, 80);
        int t = rnd.next(1, n);
        k = clampK(n, maxInversions(t) + rnd.next(-t, t));
    } else {
        n = rnd.next(1, 500);
        k = rnd.next(0, maxInversions(n));
    }

    println(n, k);
    return 0;
}
