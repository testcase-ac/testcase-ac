#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long watched(long long first) {
    __int128 total = 0;
    for (int day = 0; day < 7; ++day) {
        total += max(0LL, first - day);
    }
    return static_cast<long long>(total);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 100000000000000000LL;

    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 20LL);
    } else if (mode == 1) {
        vector<long long> edges = {1, 2, 3, 4, 5, 6, 7, 8, 28, 57, MAX_N};
        n = rnd.any(edges);
    } else if (mode == 2) {
        long long first = rnd.next(1LL, 20LL);
        long long base = watched(first);
        long long lo = max(1LL, base - 2);
        long long hi = min(MAX_N, base + 2);
        n = rnd.next(lo, hi);
    } else if (mode == 3) {
        long long first = rnd.next(21LL, 1000000LL);
        long long base = watched(first);
        long long lo = max(1LL, base - rnd.next(0LL, 8LL));
        long long hi = min(MAX_N, base + rnd.next(0LL, 8LL));
        n = rnd.next(lo, hi);
    } else if (mode == 4) {
        long long first = rnd.next(1000000LL, 14285714285714291LL);
        long long base = watched(first);
        long long lo = max(1LL, base - rnd.next(0LL, 20LL));
        long long hi = min(MAX_N, base + rnd.next(0LL, 20LL));
        n = rnd.next(lo, hi);
    } else {
        long long delta = rnd.next(0LL, 1000000LL);
        n = MAX_N - delta;
    }

    println(n);
    return 0;
}
