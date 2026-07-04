#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long clampN(long long value) {
    return max(2LL, min(value, 1000000000000000LL));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxN = 1000000000000000LL;
    int mode = rnd.next(0, 7);
    long long n = 2;
    int k = 0;

    if (mode == 0) {
        n = rnd.next(2LL, 200LL);
        k = rnd.next(0, 12);
    } else if (mode == 1) {
        int bit = rnd.next(1, 49);
        long long base = 1LL << bit;
        long long delta = rnd.next(-5LL, 5LL);
        n = clampN(base + delta);
        k = rnd.next(0, min(50, bit + 3));
    } else if (mode == 2) {
        int bit = rnd.next(2, 49);
        long long base = (1LL << bit) - 1;
        long long delta = rnd.next(-8LL, 8LL);
        n = clampN(base + delta);
        k = rnd.next(0, min(50, bit + 2));
    } else if (mode == 3) {
        n = rnd.next(1000000LL, 1000000000LL);
        k = rnd.next(0, 7);
    } else if (mode == 4) {
        n = rnd.next(1000000001LL, maxN);
        k = rnd.next(0, 50);
    } else if (mode == 5) {
        vector<long long> special = {
            2LL,
            3LL,
            15LL,
            1234567LL,
            1000000000LL,
            maxN - 1,
            maxN
        };
        n = rnd.any(special);
        k = rnd.next(0, 50);
    } else if (mode == 6) {
        n = rnd.next(2LL, 100000LL);
        k = rnd.next(35, 50);
    } else {
        int bits = rnd.next(2, 49);
        long long mask = 0;
        for (int i = 0; i < bits; ++i) {
            if (rnd.next(0, 1)) {
                mask |= (1LL << i);
            }
        }
        n = clampN(mask + 2);
        k = rnd.next(0, 50);
    }

    println(n, k);
    return 0;
}
