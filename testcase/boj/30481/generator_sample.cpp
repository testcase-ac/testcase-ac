#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

using int64 = long long;

const int64 MIN_N = 2;
const int64 MAX_N = 1000000000000LL;

int64 bounded(int64 value) {
    return max(MIN_N, min(MAX_N, value));
}

int64 randomPowerNeighbor() {
    vector<int64> bases = {2, 3, 4, 5, 10, 16, 31, 32, 100, 1000};
    int64 base = rnd.any(bases);
    int64 value = 1;
    while (value <= MAX_N / base && rnd.next(2))
        value *= base;

    int64 delta = rnd.next(-3, 3);
    return bounded(value + delta);
}

int64 randomTwoDigitPalindromeValue() {
    int64 s = rnd.next(1LL, 1000000LL);
    int64 maxBase = MAX_N / s - 1;
    if (maxBase < 2)
        return rnd.next(MIN_N, MAX_N);

    int64 base;
    if (maxBase <= 1000000)
        base = rnd.next(2LL, maxBase);
    else
        base = rnd.next(2LL, 1000000LL);

    return bounded(s * (base + 1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int64 n;
    int mode = rnd.next(6);
    if (mode == 0) {
        n = rnd.next(MIN_N, 50LL);
    } else if (mode == 1) {
        n = MAX_N - rnd.next(0LL, 1000000LL);
    } else if (mode == 2) {
        n = randomPowerNeighbor();
    } else if (mode == 3) {
        n = randomTwoDigitPalindromeValue();
    } else if (mode == 4) {
        int64 hi = rnd.next(1000000LL, MAX_N);
        int64 lo = max(MIN_N, hi - rnd.next(0LL, 1000000LL));
        n = rnd.next(lo, hi);
    } else {
        n = rnd.next(MIN_N, MAX_N);
    }

    println(n);
    return 0;
}
