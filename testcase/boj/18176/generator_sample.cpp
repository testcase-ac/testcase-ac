#include "testlib.h"
#include <algorithm>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMax = 1000000000000LL;

    int mode = rnd.next(0, 8);
    long long n;
    long long m;

    if (mode == 0) {
        n = rnd.next(1LL, 40LL);
        m = rnd.next(n, min(kMax, n + rnd.next(0LL, 30LL)));
    } else if (mode == 1) {
        n = rnd.next(1LL, 2000LL);
        m = n;
    } else if (mode == 2) {
        n = rnd.next(1LL, 1000000LL);
        m = rnd.next(n, min(kMax, n + rnd.next(1LL, 1000LL)));
    } else if (mode == 3) {
        long long center = rnd.next(1LL, 1000000LL);
        center *= center;
        long long deltaLeft = rnd.next(0LL, 1000LL);
        long long deltaRight = rnd.next(0LL, 1000LL);
        n = max(1LL, center - deltaLeft);
        m = min(kMax, center + deltaRight);
    } else if (mode == 4) {
        n = rnd.next(1LL, 1000000LL);
        m = rnd.next(1000000000LL, kMax);
        if (n > m) swap(n, m);
    } else if (mode == 5) {
        m = rnd.next(kMax - 1000000LL, kMax);
        n = rnd.next(max(1LL, m - rnd.next(0LL, 10000LL)), m);
    } else if (mode == 6) {
        long long base = 1;
        int exponent = rnd.next(0, 12);
        for (int i = 0; i < exponent; ++i) base *= 10;
        n = max(1LL, base - rnd.next(0LL, min(base - 1, 1000LL)));
        m = min(kMax, base + rnd.next(0LL, 1000LL));
    } else {
        long long width = rnd.next(0LL, 100000LL);
        n = rnd.next(1LL, kMax - width);
        m = n + width;
    }

    println(n, m);
    return 0;
}
