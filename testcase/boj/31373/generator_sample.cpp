#include "testlib.h"

#include <algorithm>
#include <cstdint>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<uint64_t> values = {
        0ULL,
        1ULL,
        (1ULL << 16) - 1,
        1ULL << 16,
        1ULL << 31,
        (1ULL << 32) - 1,
    };

    int mode = rnd.next(0, 5);
    uint64_t n = 0;

    if (mode == 0) {
        n = rnd.any(values);
    } else if (mode == 1) {
        int bit = rnd.next(0, 31);
        n = 1ULL << bit;
        if (rnd.next(0, 1)) {
            n += rnd.next(0, 15);
        }
    } else if (mode == 2) {
        n = rnd.next(0, (1 << 16) - 1);
    } else if (mode == 3) {
        uint64_t low = rnd.next(0, (1 << 16) - 1);
        n = low << 16;
        if (rnd.next(0, 1)) {
            n |= rnd.next(0, 15);
        }
    } else if (mode == 4) {
        int bits = rnd.next(1, 8);
        for (int i = 0; i < bits; ++i) {
            n |= 1ULL << rnd.next(0, 31);
        }
    } else {
        uint64_t hi = rnd.next(0, (1 << 16) - 1);
        uint64_t lo = rnd.next(0, (1 << 16) - 1);
        n = (hi << 16) | lo;
    }

    println(n);
    return 0;
}
