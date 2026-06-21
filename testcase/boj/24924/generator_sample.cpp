#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxValue = 1000000000000LL;
    vector<long long> powersOfTen = {
        1LL,
        10LL,
        100LL,
        1000LL,
        10000LL,
        100000LL,
        1000000LL,
        10000000LL,
        100000000LL,
        1000000000LL,
        10000000000LL,
        100000000000LL,
        1000000000000LL,
    };

    long long l = 1;
    long long length = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        l = rnd.next(1LL, 200LL);
        length = rnd.next(1LL, 40LL);
    } else if (mode == 1) {
        long long center = rnd.any(powersOfTen);
        long long lo = max(1LL, center - 20);
        long long hi = min(maxValue, center + 20);
        l = rnd.next(lo, hi);
        length = rnd.next(1LL, 35LL);
    } else if (mode == 2) {
        l = rnd.next(maxValue - 300, maxValue);
        length = rnd.next(1LL, min(80LL, maxValue - l + 1));
    } else if (mode == 3) {
        long long block = rnd.next(1LL, 12LL) * 9LL + rnd.next(0LL, 2LL);
        length = block;
        l = rnd.next(1LL, maxValue - length + 1);
    } else if (mode == 4) {
        long long digitCount = rnd.next(1LL, 12LL);
        long long lo = powersOfTen[digitCount - 1];
        long long hi = min(maxValue, powersOfTen[digitCount] - 1);
        l = rnd.next(lo, hi);
        length = rnd.next(1LL, min(60LL, hi - l + 1));
    } else {
        length = rnd.next(1LL, 120LL);
        l = rnd.next(1LL, maxValue - length + 1);
    }

    long long r = l + length - 1;
    println(l, r);
    return 0;
}
