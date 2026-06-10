#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

const long long MAX_N = 1000000000000000000LL;

long long clampValue(__int128 value) {
    if (value < 1) return 1;
    if (value > MAX_N) return MAX_N;
    return static_cast<long long>(value);
}

long long powLimited(long long base, int exp) {
    __int128 value = 1;
    for (int i = 0; i < exp; ++i) {
        value *= base;
        if (value > MAX_N) return MAX_N + 1;
    }
    return static_cast<long long>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> anchors = {
        1,
        2,
        3,
        4,
        8,
        9,
        16,
        27,
        80,
        123456789,
        MAX_N
    };

    int mode = rnd.next(0, 6);
    long long n = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        n = rnd.next(1LL, 1000000LL);
    } else if (mode == 2) {
        long long hi = rnd.next(1000000000000LL, MAX_N);
        long long lo = max(1LL, hi - rnd.next(0LL, 1000000LL));
        n = rnd.next(lo, hi);
    } else if (mode == 3) {
        long long base = rnd.next(2LL, 1000000LL);
        int exp = rnd.next(2, 12);
        while (powLimited(base, exp) > MAX_N && base > 2) {
            base = rnd.next(2LL, max(2LL, base / 2));
        }
        n = powLimited(base, exp);
        if (n > MAX_N) n = powLimited(2, rnd.next(2, 59));
    } else if (mode == 4) {
        long long base = rnd.next(2LL, 1000000LL);
        int exp = rnd.next(2, 12);
        while (powLimited(base, exp) > MAX_N && base > 2) {
            base = rnd.next(2LL, max(2LL, base / 2));
        }
        long long power = powLimited(base, exp);
        if (power > MAX_N) power = powLimited(2, rnd.next(2, 59));
        long long delta = rnd.next(-1000LL, 1000LL);
        if (delta == 0) delta = rnd.next(0, 1) ? 1 : -1;
        n = clampValue(static_cast<__int128>(power) + delta);
    } else if (mode == 5) {
        long long base = rnd.next(999999900LL, 1000000000LL);
        long long delta = rnd.next(-1000000LL, 1000000LL);
        n = clampValue(static_cast<__int128>(base) * base + delta);
    } else {
        long long anchor = rnd.any(anchors);
        long long delta = rnd.next(-100LL, 100LL);
        n = clampValue(static_cast<__int128>(anchor) + delta);
    }

    println(n);
    return 0;
}
