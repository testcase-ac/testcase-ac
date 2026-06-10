#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000000000000LL;

    auto randomWide = [&]() {
        long long high = rnd.next(0, 1000000000);
        long long low = rnd.next(0, 999999999);
        return min(MAX_VALUE, high * 1000000000LL + low);
    };

    auto nearValue = [&](long long center, long long radius) {
        long long lo = max(0LL, center - radius);
        long long hi = min(MAX_VALUE, center + radius);
        return rnd.next(lo, hi);
    };

    int mode = rnd.next(0, 6);
    long long x0 = 0;
    long long n = 0;

    if (mode == 0) {
        x0 = rnd.next(0LL, 64LL);
        n = rnd.next(0LL, 128LL);
    } else if (mode == 1) {
        int bit = rnd.next(0, 59);
        x0 = nearValue(1LL << bit, rnd.next(0LL, 12LL));
        n = rnd.next(0LL, 1000000LL);
    } else if (mode == 2) {
        x0 = randomWide();
        if (rnd.next(0, 1) == 0) x0 &= ~1LL;
        else x0 |= 1LL;
        n = rnd.next(0LL, 10000LL);
    } else if (mode == 3) {
        x0 = nearValue(MAX_VALUE, rnd.next(0LL, 1000000LL));
        n = rnd.next(0LL, MAX_VALUE);
    } else if (mode == 4) {
        x0 = randomWide();
        n = rnd.next(0LL, 32LL);
    } else {
        x0 = randomWide();
        n = randomWide();
    }

    println(x0, n);
    return 0;
}
