#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

// Generates varied valid intervals for counting left-truncation-by-suffix-prefix primes.
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_VALUE = 1000000000000000000LL;

    vector<long long> anchors = {
        1LL,
        2LL,
        3LL,
        5LL,
        7LL,
        20LL,
        23LL,
        29LL,
        31LL,
        37LL,
        53LL,
        73LL,
        113LL,
        197LL,
        313LL,
        797LL,
        2333LL,
        3137LL,
        73939133LL,
        100000000000000000LL,
        MAX_VALUE
    };

    vector<long long> powers;
    long long p = 1;
    for (int i = 0; i <= 18; ++i) {
        powers.push_back(p);
        if (p <= MAX_VALUE / 10) p *= 10;
    }

    long long a = 1;
    long long b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1LL, 100LL);
        b = rnd.next(a, min(MAX_VALUE, a + rnd.next(0LL, 50LL)));
    } else if (mode == 1) {
        long long center = rnd.any(anchors);
        long long left = rnd.next(0LL, min(center - 1, 200LL));
        long long right = rnd.next(0LL, min(MAX_VALUE - center, 200LL));
        a = center - left;
        b = center + right;
    } else if (mode == 2) {
        long long center = rnd.any(powers);
        long long left = rnd.next(0LL, min(center - 1, 1000LL));
        long long right = rnd.next(0LL, min(MAX_VALUE - center, 1000LL));
        a = center - left;
        b = center + right;
    } else if (mode == 3) {
        long long span = rnd.next(0LL, 1000000LL);
        a = rnd.next(max(1LL, MAX_VALUE - 1000000000000LL), MAX_VALUE - span);
        b = a + span;
    } else if (mode == 4) {
        long long lo = rnd.next(1LL, 1000000LL);
        long long hi = rnd.next(lo, min(MAX_VALUE, lo + rnd.next(0LL, 1000000000LL)));
        a = lo;
        b = hi;
    } else {
        long long width = rnd.next(0LL, 10000LL);
        long long upper = MAX_VALUE - width;
        a = rnd.next(1LL, upper);
        b = a + width;
    }

    println(a, b);
    return 0;
}
