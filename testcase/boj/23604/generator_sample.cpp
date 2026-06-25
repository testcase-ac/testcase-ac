#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long kMaxValue = 1000000000000000000LL;

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 5) {
        n = rnd.next(40, 120);
    } else {
        n = rnd.next(2, 12);
    }

    vector<long long> a(n), b(n);
    long long baseGcd = 1;
    if (mode == 1) {
        vector<long long> choices = {2, 3, 4, 6, 12, 36, 1000000000LL};
        baseGcd = rnd.any(choices);
    } else if (mode == 2) {
        baseGcd = 1;
    } else if (mode == 4) {
        baseGcd = rnd.next(1LL, 1000000LL);
    } else {
        baseGcd = rnd.next(1LL, 1000LL);
    }

    bool hasDifferentPair = false;
    for (int i = 0; i < n; ++i) {
        if (mode == 3 && rnd.next(0, 2) == 0) {
            b[i] = rnd.next(0LL, 1000LL);
            a[i] = b[i];
            continue;
        }

        long long maxMultiplier = max(1LL, kMaxValue / baseGcd);
        long long multiplier = 1;
        if (mode == 0) {
            multiplier = rnd.next(1LL, min(1000000LL, maxMultiplier));
        } else if (mode == 4) {
            multiplier = rnd.next(max(1LL, maxMultiplier - 1000LL), maxMultiplier);
        } else {
            multiplier = rnd.next(1LL, min(10000LL, maxMultiplier));
        }

        long long diff = baseGcd * multiplier;
        long long upperB = kMaxValue - diff;
        if (mode == 4) {
            b[i] = rnd.next(max(0LL, upperB - 1000000LL), upperB);
        } else if (mode == 2 && i == 0) {
            b[i] = rnd.next(0LL, min(1000LL, upperB));
            diff = 1;
        } else {
            b[i] = rnd.next(0LL, min(1000000LL, upperB));
        }
        a[i] = b[i] + diff;
        hasDifferentPair = true;
    }

    if (!hasDifferentPair) {
        a[0] = b[0] + 1;
    }

    println(n);
    println(a);
    println(b);

    return 0;
}
