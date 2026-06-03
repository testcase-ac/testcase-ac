#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

using namespace std;

const long long INT32_MAX_VALUE = 2147483647LL;

pair<long long, long long> reduceFraction(long long p, long long q) {
    long long g = gcd(p, q);
    return {p / g, q / g};
}

pair<long long, long long> fromTreePath(int steps) {
    long long p = 1;
    long long q = 1;
    for (int i = 0; i < steps; ++i) {
        if (rnd.next(2) == 0) {
            q += p;
        } else {
            p += q;
        }
    }
    return {p, q};
}

pair<long long, long long> randomSmallReduced() {
    while (true) {
        long long p = rnd.next(1, 200);
        long long q = rnd.next(1, 200);
        if (gcd(p, q) == 1) {
            return {p, q};
        }
    }
}

pair<long long, long long> makeCase(int mode) {
    if (mode == 0) {
        return fromTreePath(rnd.next(0, 22));
    }
    if (mode == 1) {
        return {1, rnd.next(1, 1000000)};
    }
    if (mode == 2) {
        return {rnd.next(1, 1000000), 1};
    }
    if (mode == 3) {
        return randomSmallReduced();
    }
    if (mode == 4) {
        long long q = rnd.next(INT32_MAX_VALUE - 1000000, INT32_MAX_VALUE);
        long long p = rnd.next(1, 1000000);
        return reduceFraction(p, q);
    }
    if (mode == 5) {
        long long q = rnd.next(1, 1000000);
        long long p = q * rnd.next(1LL, 2000LL) + rnd.next(1LL, q);
        return reduceFraction(p, q);
    }

    vector<pair<long long, long long>> edges = {
        {1, 1},
        {1, INT32_MAX_VALUE},
        {INT32_MAX_VALUE - 1, 1},
        {INT32_MAX_VALUE, INT32_MAX_VALUE - 1},
        {2178309, 1346269},
    };
    return rnd.any(edges);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int pCount = rnd.next(4, 20);
    println(pCount);

    for (int i = 1; i <= pCount; ++i) {
        auto [p, q] = makeCase(rnd.next(0, 6));
        println(i, format("%lld/%lld", p, q));
    }

    return 0;
}
