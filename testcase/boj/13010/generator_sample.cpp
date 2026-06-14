#include "testlib.h"
#include <cstdint>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long divisorCount(long long x) {
    long long result = 0;
    for (long long d = 1; d * d <= x; ++d) {
        if (x % d == 0) {
            ++result;
            if (d != x / d) ++result;
        }
    }
    return result;
}

long long limitedPower(long long base, long long exponent) {
    __int128 value = 1;
    for (long long i = 0; i < exponent; ++i) {
        value *= base;
        if (value > LIMIT) return LIMIT + 1;
    }
    return (long long)value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> images;
    for (long long x = 2; x <= 200000; ++x) {
        long long value = limitedPower(x, divisorCount(x));
        if (value <= LIMIT) images.push_back(value);
    }

    vector<long long> edgeValues = {
        2,
        3,
        4,
        8,
        16,
        64,
        10000,
        LIMIT - 2,
        LIMIT - 1,
        LIMIT
    };

    int mode = rnd.next(0, 4);
    long long n = 2;

    if (mode == 0) {
        n = rnd.any(images);
    } else if (mode == 1) {
        long long base = rnd.any(images);
        long long delta = rnd.next(1, 1000);
        if (base <= 2 + delta) {
            n = base + delta;
        } else if (base + delta > LIMIT) {
            n = base - delta;
        } else {
            n = base + (rnd.next(0, 1) == 0 ? -delta : delta);
        }
    } else if (mode == 2) {
        long long base = rnd.next(2LL, 1000000LL);
        int exponent = rnd.next(2, 10);
        while (limitedPower(base, exponent) > LIMIT) {
            base = rnd.next(2LL, 1000000LL);
            exponent = rnd.next(2, 10);
        }
        n = limitedPower(base, exponent);
    } else if (mode == 3) {
        if (rnd.next(0, 1) == 0) {
            n = rnd.next(2LL, 1000000LL);
        } else {
            n = rnd.next(2LL, LIMIT);
        }
    } else {
        n = rnd.any(edgeValues);
    }

    println(n);
    return 0;
}
