#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MIN_N = 1;
    const long long MAX_N = 10000000000000LL;
    const long long MAX_ROOT = 3162277LL;

    vector<long long> interesting = {
        1LL,
        2LL,
        3LL,
        4LL,
        5LL,
        6LL,
        12LL,
        13LL,
        36LL,
        68LL,
        999LL,
        1000LL,
        100000LL,
        5000000LL,
        100000000LL,
        10000000000LL,
        MAX_N
    };

    int mode = rnd.next(0, 6);
    long long n;
    if (mode == 0) {
        n = rnd.next(1LL, 200LL);
    } else if (mode == 1) {
        n = rnd.any(interesting);
    } else if (mode == 2) {
        long long root = rnd.next(1LL, 1000000LL);
        long long offset = rnd.next(-3LL, 3LL);
        n = root * root + offset;
    } else if (mode == 3) {
        long long root = rnd.next(2LL, MAX_ROOT);
        long long multiplier = rnd.next(1LL, max(1LL, MAX_N / (root * root)));
        n = root * root * multiplier + rnd.next(-2LL, 2LL);
    } else if (mode == 4) {
        n = rnd.next(1LL, 100000000LL);
    } else if (mode == 5) {
        n = rnd.next(100000000LL, 10000000000LL);
    } else {
        n = MAX_N - rnd.next(0LL, 1000000LL);
    }

    n = max(MIN_N, min(MAX_N, n));
    println(n);
    return 0;
}
