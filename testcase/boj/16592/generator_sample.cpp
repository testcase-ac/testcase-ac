#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_PLATE = 10000000000000000LL;

long long clampPlate(long long x) {
    return max(1LL, min(MAX_PLATE, x));
}

long long pow10(int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; ++i) value *= 10;
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long a = 1;
    long long b = 1;

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
        b = clampPlate(a + rnd.next(0LL, 80LL));
    } else if (mode == 1) {
        vector<long long> values = {
            1LL,
            2LL,
            5LL,
            9LL,
            10LL,
            20LL,
            100LL,
            1000LL,
            MAX_PLATE,
        };
        a = b = rnd.any(values);
    } else if (mode == 2) {
        long long center = pow10(rnd.next(1, 16));
        long long radius = rnd.next(0LL, min(250LL, center - 1));
        a = clampPlate(center - radius);
        b = clampPlate(center + rnd.next(0LL, 250LL));
    } else if (mode == 3) {
        int zeros = rnd.next(1, 12);
        long long unit = pow10(zeros);
        long long multiplier = rnd.next(1LL, min(9999LL, MAX_PLATE / unit));
        long long center = multiplier * unit;
        long long radius = rnd.next(0LL, min(500LL, unit - 1));
        a = clampPlate(center - radius);
        b = clampPlate(center + rnd.next(0LL, radius + 20));
    } else if (mode == 4) {
        long long span = rnd.next(0LL, 1000LL);
        b = MAX_PLATE - rnd.next(0LL, 1000LL);
        a = b - span;
    } else {
        long long base = rnd.next(1LL, MAX_PLATE);
        long long span = rnd.next(0LL, 10000LL);
        a = base;
        b = clampPlate(base + span);
    }

    if (a > b) swap(a, b);

    println(a, b);
    return 0;
}
