#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxA = 1000000000000000000LL;
    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        10LL,
        50LL,
        1234LL,
        1000000LL,
        1000000000000LL,
        maxA
    };

    int mode = rnd.next(0, 6);
    long long a = 1;

    if (mode == 0) {
        a = rnd.next(1LL, 100LL);
    } else if (mode == 1) {
        long long base = rnd.any(anchors);
        long long delta = rnd.next(-20LL, 20LL);
        a = max(1LL, min(maxA, base + delta));
    } else if (mode == 2) {
        long long r = rnd.next(1LL, 1000000LL);
        a = r * r;
    } else if (mode == 3) {
        long long lo = rnd.next(1LL, 1000000000LL);
        long long hi = rnd.next(lo, 1000000000LL);
        a = lo * hi;
    } else if (mode == 4) {
        long long magnitude = rnd.next(1LL, 18LL);
        a = 1;
        for (int i = 0; i < magnitude; ++i) a *= 10;
        a += rnd.next(-999LL, 999LL);
        a = max(1LL, min(maxA, a));
    } else {
        a = maxA - rnd.next(0LL, 1000000LL);
    }

    println(a);
    return 0;
}
