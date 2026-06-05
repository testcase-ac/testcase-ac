#include "testlib.h"

#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;

    if (mode == 6) {
        n = rnd.next(100000, 314159);
    } else if (mode == 7) {
        n = 314159;
    } else {
        n = rnd.next(1, 30);
    }

    long long maxInversions = 1LL * n * (n - 1) / 2;
    long long k;

    if (mode == 0) {
        k = 0;
    } else if (mode == 1) {
        k = maxInversions;
    } else if (mode == 2) {
        k = rnd.next(0LL, min(maxInversions, 10LL));
    } else if (mode == 3) {
        long long delta = rnd.next(0LL, min(maxInversions, 10LL));
        k = maxInversions - delta;
    } else if (mode == 4) {
        k = maxInversions / 2 + rnd.next(-min(maxInversions / 2, 10LL), min((maxInversions + 1) / 2, 10LL));
    } else {
        k = rnd.next(0LL, maxInversions);
    }

    println(n, k);
    return 0;
}
