#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long limit = 1000000000000LL;
    long long n = 0;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(0LL, 20LL);
    } else if (mode == 1) {
        int bit = rnd.next(0, 39);
        n = 1LL << bit;
    } else if (mode == 2) {
        int bit = rnd.next(1, 39);
        long long base = 1LL << bit;
        long long delta = rnd.next(-3LL, 3LL);
        n = base + delta;
    } else if (mode == 3) {
        int digits = rnd.next(1, 12);
        long long high = 1;
        for (int i = 0; i < digits; ++i) high *= 10;
        long long low = high / 10;
        n = rnd.next(low, high - 1);
    } else if (mode == 4) {
        n = limit - rnd.next(0LL, 1000000LL);
    } else {
        vector<long long> anchors = {
            0LL,
            1LL,
            2LL,
            3LL,
            6LL,
            2147483647LL,
            2147483648LL,
            2147483649LL,
            549755813887LL,
            549755813888LL,
            549755813889LL,
            limit,
        };
        n = rnd.any(anchors);
    }

    n = max(0LL, min(limit, n));
    println(n);
    return 0;
}
