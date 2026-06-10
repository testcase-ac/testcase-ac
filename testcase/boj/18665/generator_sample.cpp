#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;
    vector<long long> special = {
        0LL,
        1LL,
        2LL,
        3LL,
        4LL,
        5LL,
        7LL,
        8LL,
        15LL,
        16LL,
        17LL,
        999999999999999999LL,
        LIMIT
    };

    int mode = rnd.next(0, 6);
    long long n = 0;

    if (mode == 0) {
        n = rnd.any(special);
    } else if (mode == 1) {
        n = rnd.next(0LL, 1000LL);
    } else if (mode == 2) {
        long long root = rnd.next(0LL, 1000000000LL);
        n = root * root;
    } else if (mode == 3) {
        long long root = rnd.next(2LL, 1000000000LL);
        long long gap = rnd.next(1LL, min(1000LL, root * root));
        n = root * root - gap;
    } else if (mode == 4) {
        long long root = rnd.next(1LL, 1000000000LL);
        long long base = root * root;
        long long delta = rnd.next(0LL, min(1000LL, LIMIT - base));
        n = base + delta;
    } else if (mode == 5) {
        long long bit = rnd.next(0LL, 60LL);
        n = 1LL << bit;
        long long delta = rnd.next(-1000LL, 1000LL);
        if (delta < 0) {
            n -= min(n, -delta);
        } else {
            n += min(LIMIT - n, delta);
        }
    } else {
        n = rnd.next(0LL, LIMIT);
    }

    println(n);
    return 0;
}
