#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampN(long long value) {
    return static_cast<int>(max(1LL, min(2000000000LL, value)));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> anchors = {
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
        59, 60, 61,
        999, 1000, 1001,
        999999, 1000000, 1000001,
        1999999998, 1999999999, 2000000000
    };

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 80);
    } else if (mode == 1) {
        int base = rnd.any(anchors);
        n = clampN(static_cast<long long>(base) + rnd.next(-3, 3));
    } else if (mode == 2) {
        int exponent = rnd.next(1, 30);
        long long base = 1LL << exponent;
        n = clampN(base + rnd.next(-5, 5));
    } else if (mode == 3) {
        int block = rnd.next(0, 4);
        int lo = block == 0 ? 1 : block == 1 ? 61 : block == 2 ? 1001 : 1000001;
        int hi = block == 0 ? 60 : block == 1 ? 1000 : block == 2 ? 1000000 : 2000000000;
        n = rnd.next(lo, hi);
    } else if (mode == 4) {
        n = rnd.next(1, 1000000);
        if (rnd.next(0, 1)) ++n;
    } else {
        n = rnd.next(1999999000, 2000000000);
    }

    println(n);
    return 0;
}
