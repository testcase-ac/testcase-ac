#include "testlib.h"

#include <algorithm>
#include <cstdint>

using namespace std;

using ull = unsigned long long;

static ull random64() {
    ull value = 0;
    for (int i = 0; i < 4; ++i) {
        value = (value << 16) | static_cast<ull>(rnd.next(0, 65535));
    }
    return value;
}

static ull randULL(ull lo, ull hi) {
    if (lo == hi) return lo;

    __uint128_t span = static_cast<__uint128_t>(hi) - lo + 1;
    __uint128_t bucket = (static_cast<__uint128_t>(1) << 64) / span;
    __uint128_t limit = bucket * span;

    ull value;
    do {
        value = random64();
    } while (static_cast<__uint128_t>(value) >= limit);

    return static_cast<ull>(static_cast<__uint128_t>(lo) + value % span);
}

static ull clampA(__uint128_t value) {
    const ull maxA = 18446744073709551614ULL;
    if (value < 1) return 1;
    if (value > maxA) return maxA;
    return static_cast<ull>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const ull maxN = 4294967295ULL;
    const ull maxA = 18446744073709551614ULL;

    ull n = 1;
    ull a = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        n = randULL(1, 25);
        a = randULL(1, min<ull>(1000, maxA));
    } else if (mode == 1) {
        ull center = 1ULL << rnd.next(1, 32);
        ull delta = randULL(0, min<ull>(center - 1, 1000));
        n = rnd.next(0, 1) ? center - delta : min(maxN, center + delta);
        n = max<ull>(1, n);
        a = randULL(1, min<ull>(maxA, static_cast<ull>(1000000000)));
    } else if (mode == 2) {
        n = maxN - randULL(0, 100000);
        a = randULL(1, maxA);
    } else if (mode == 3) {
        n = randULL(2, 1000000);
        ull k = randULL(1, 1000000);
        ull offset = randULL(0, n - 1);
        a = clampA(static_cast<__uint128_t>(k) * n + offset);
    } else if (mode == 4) {
        n = randULL(2, 100000);
        __uint128_t nearSquare = static_cast<__uint128_t>(n) * n;
        ull wiggle = randULL(0, min<ull>(1000000, maxA));
        if (rnd.next(0, 1)) {
            a = clampA(nearSquare + wiggle);
        } else {
            a = clampA(nearSquare > wiggle ? nearSquare - wiggle : 1);
        }
    } else {
        n = randULL(1, maxN);
        ull span = randULL(0, 1000000);
        a = maxA - span;
    }

    println(n, a);
    return 0;
}
