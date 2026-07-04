#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long MAX_N = 1000000000000LL;

long long clampN(long long n) {
    return max(1LL, min(MAX_N, n));
}

long long thresholdForLength(long long k) {
    return clampN((9 * k * k + 3) / 4);
}

long long randomAround(long long center, long long radius) {
    long long lo = clampN(center - radius);
    long long hi = clampN(center + radius);
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        long long k = rnd.next(1LL, 120LL);
        n = randomAround(thresholdForLength(k), rnd.next(0LL, 8LL));
    } else if (mode == 2) {
        long long k = rnd.any(vector<long long>{1, 2, 3, 4, 5, 10, 100, 1000, 10000, 100000, 666667});
        n = randomAround(thresholdForLength(k), rnd.next(0LL, max(1LL, k / 2)));
    } else if (mode == 3) {
        long long base = rnd.any(vector<long long>{
            999LL,
            1000LL,
            999999LL,
            1000000LL,
            999999999LL,
            1000000000LL,
            999999999999LL,
            MAX_N,
        });
        n = randomAround(base, rnd.next(0LL, 1000LL));
    } else if (mode == 4) {
        long long lo = rnd.next(1LL, 1000000LL);
        long long hi = rnd.next(lo, MAX_N);
        n = rnd.next(lo, hi);
    } else {
        n = rnd.next(1LL, MAX_N);
    }

    println(n);
    return 0;
}
