#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long limit = 1000000000000000000LL;
    vector<long long> powers5;
    for (long long x = 1; x <= limit / 5; x *= 5) {
        powers5.push_back(x);
    }
    powers5.push_back(limit);

    long long n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1LL, 100LL);
    } else if (mode == 1) {
        long long p = rnd.any(powers5);
        long long delta = rnd.next(-20LL, 20LL);
        n = min(limit, max(1LL, p + delta));
    } else if (mode == 2) {
        vector<long long> scales = {
            10LL,
            100LL,
            1000LL,
            10000LL,
            100000LL,
            1000000LL,
            1000000000LL,
            1000000000000LL,
            1000000000000000LL,
            limit,
        };
        long long s = rnd.any(scales);
        long long delta = rnd.next(-1000LL, 1000LL);
        n = min(limit, max(1LL, s + delta));
    } else if (mode == 3) {
        long long high = rnd.next(1000000LL, limit);
        long long low = rnd.next(1LL, high);
        n = rnd.next(low, high);
    } else if (mode == 4) {
        long long block = rnd.next(1LL, 1000000000LL);
        long long offset = rnd.next(0LL, 1000LL);
        n = min(limit, block * 1000000000LL + offset);
    } else {
        n = rnd.next(1LL, limit);
    }

    println(n);
    return 0;
}
