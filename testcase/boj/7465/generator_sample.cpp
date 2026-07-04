#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long MAX_N = 100000000000000LL;

long long sumSquares(long long first, int length) {
    __int128 sum = 0;
    for (int i = 0; i < length; ++i) {
        long long x = first + i;
        sum += static_cast<__int128>(x) * x;
    }
    return static_cast<long long>(sum);
}

long long maxStartForLength(int length) {
    long long lo = 1;
    long long hi = 10000000;
    while (lo < hi) {
        long long mid = (lo + hi + 1) / 2;
        if (sumSquares(mid, length) <= MAX_N) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }
    return lo;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.next(1LL, 5000LL);
    } else if (mode == 1) {
        int length = rnd.next(2, 12);
        long long first = rnd.next(1LL, 250LL);
        n = sumSquares(first, length);
    } else if (mode == 2) {
        int length = rnd.next(2, 8);
        long long first = rnd.next(1LL, maxStartForLength(length));
        n = sumSquares(first, length);
    } else if (mode == 3) {
        int length = rnd.next(2, 10);
        long long first = rnd.next(1LL, maxStartForLength(length));
        long long base = sumSquares(first, length);
        long long delta = rnd.next(-25LL, 25LL);
        if (delta == 0) delta = 1;
        n = max(1LL, min(MAX_N, base + delta));
    } else if (mode == 4) {
        n = rnd.any(vector<long long>{
            1LL,
            2LL,
            3LL,
            4LL,
            5LL,
            MAX_N - rnd.next(0LL, 1000LL),
            MAX_N
        });
    } else {
        long long hi = rnd.next(1000000LL, MAX_N);
        long long lo = rnd.next(1LL, min(hi, 1000000000LL));
        n = rnd.next(lo, hi);
    }

    println(n);
    return 0;
}
