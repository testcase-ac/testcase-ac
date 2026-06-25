#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long kMaxValue = 1LL << 60;

long long randomValue(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

long long clampValue(long long x) {
    return max(1LL, min(kMaxValue, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n;
    int k;
    long long a;
    long long b;

    int mode = rnd.next(0, 6);
    if (mode == 0) {
        n = randomValue(1, 64);
        k = rnd.next(0, 6);
        a = randomValue(1, 64);
        b = randomValue(a, 128);
    } else if (mode == 1) {
        int bit = rnd.next(0, 60);
        long long pivot = 1LL << bit;
        n = clampValue(pivot + rnd.next(-3LL, 3LL));
        k = rnd.next(max(0, bit - 2), min(60, bit + 2));
        a = clampValue(pivot + rnd.next(-8LL, 4LL));
        b = clampValue(pivot + rnd.next(0LL, 16LL));
        if (a > b) swap(a, b);
    } else if (mode == 2) {
        n = randomValue(kMaxValue - 2048, kMaxValue);
        k = rnd.next(55, 60);
        a = randomValue(kMaxValue - 4096, kMaxValue);
        b = randomValue(a, kMaxValue);
    } else if (mode == 3) {
        n = randomValue(1, kMaxValue);
        k = rnd.any(vector<int>{0, 1, 2, 58, 59, 60});
        a = randomValue(1, kMaxValue);
        b = a;
    } else if (mode == 4) {
        long long anchor = randomValue(1, kMaxValue);
        long long width = randomValue(0, 256);
        n = anchor ^ randomValue(0, 1023);
        n = clampValue(n);
        k = rnd.next(0, 60);
        a = clampValue(anchor - rnd.next(0LL, width));
        b = clampValue(anchor + rnd.next(0LL, width));
        if (a > b) swap(a, b);
    } else {
        n = randomValue(1, kMaxValue);
        k = rnd.next(0, 60);
        a = randomValue(1, kMaxValue);
        b = randomValue(a, kMaxValue);
    }

    println(n, k, a, b);
    return 0;
}
