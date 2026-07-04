#include "testlib.h"

#include <algorithm>
#include <cmath>

using namespace std;

int ceilSqrt(int n) {
    int r = (int)sqrt((double)n);
    while (1LL * r * r < n) ++r;
    while (r > 0 && 1LL * (r - 1) * (r - 1) >= n) --r;
    return r;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 25);
        k = rnd.next(1, n);
    } else if (mode == 1) {
        n = rnd.next(2, 80);
        int need = ceilSqrt(n);
        k = rnd.next(1, max(1, need - 1));
    } else if (mode == 2) {
        n = rnd.next(2, 120);
        k = ceilSqrt(n);
    } else if (mode == 3) {
        int root = rnd.next(2, 12);
        n = root * root;
        k = rnd.next(max(1, root - 1), root);
    } else if (mode == 4) {
        int root = rnd.next(2, 12);
        n = root * root + rnd.next(1, root);
        int need = ceilSqrt(n);
        k = rnd.next(max(1, need - 2), min(n, need + 2));
    } else if (mode == 5) {
        n = rnd.next(80, 250);
        int need = ceilSqrt(n);
        k = rnd.next(need, min(n, need + rnd.next(0, 25)));
    } else if (mode == 6) {
        n = rnd.next(2, 250);
        int need = ceilSqrt(n);
        k = rnd.next(need, n);
    } else {
        n = rnd.next(1, 250);
        k = rnd.next(max(1, n - 20), n);
    }

    println(n, k);
    return 0;
}
