#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long clampValue(__int128 value) {
    const long long limit = 1000000000000000000LL;
    if (value < 1) return 1;
    if (value > limit) return limit;
    return static_cast<long long>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long limit = 1000000000000000000LL;
    int mode = rnd.next(0, 6);
    long long n = 1;
    long long m = 1;

    if (mode == 0) {
        n = rnd.next(1LL, 40LL);
        m = rnd.next(1LL, 12LL);
    } else if (mode == 1) {
        m = rnd.next(1LL, 30LL);
        long long k = rnd.next(0LL, 30LL);
        n = clampValue(1 + (__int128)k * (m + 1));
    } else if (mode == 2) {
        m = rnd.next(1LL, 40LL);
        long long k = rnd.next(0LL, 25LL);
        long long offset = rnd.next(1LL, m);
        n = clampValue(1 + (__int128)k * (m + 1) + offset);
    } else if (mode == 3) {
        m = 1;
        n = rnd.next(1LL, 200LL);
    } else if (mode == 4) {
        m = rnd.next(limit - 1000, limit);
        n = rnd.next(1LL, limit);
    } else if (mode == 5) {
        m = rnd.next(1LL, 1000000LL);
        long long maxK = (limit - 1) / (m + 1);
        long long k = maxK == 0 ? 0 : rnd.next(max(0LL, maxK - 1000), maxK);
        long long offset = rnd.next(0LL, m);
        n = clampValue(1 + (__int128)k * (m + 1) + offset);
    } else {
        vector<pair<long long, long long>> edges = {
            {1, 1},
            {2, 1},
            {limit, 1},
            {limit, limit},
            {limit - rnd.next(0LL, 1000LL), rnd.next(1LL, 1000LL)}
        };
        auto chosen = rnd.any(edges);
        n = chosen.first;
        m = chosen.second;
    }

    println(n, m);
    return 0;
}
