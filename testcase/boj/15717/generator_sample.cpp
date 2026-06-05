#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_N = 1000000000000LL;
    vector<long long> anchors = {
        0LL,
        1LL,
        2LL,
        3LL,
        10LL,
        1000LL,
        1000000006LL,
        1000000007LL,
        1000000008LL,
        MAX_N - 2,
        MAX_N - 1,
        MAX_N,
    };

    int mode = rnd.next(0, 5);
    long long n;

    if (mode == 0) {
        n = rnd.any(anchors);
    } else if (mode == 1) {
        n = rnd.next(0LL, 50LL);
    } else if (mode == 2) {
        int exponent = rnd.next(0, 39);
        long long base = 1LL << exponent;
        long long delta = rnd.next(-3LL, 3LL);
        n = max(0LL, min(MAX_N, base + delta));
    } else if (mode == 3) {
        long long block = rnd.next(0LL, MAX_N / 1000000007LL);
        long long offset = rnd.next(-5LL, 5LL);
        n = max(0LL, min(MAX_N, block * 1000000007LL + offset));
    } else if (mode == 4) {
        n = MAX_N - rnd.next(0LL, 1000LL);
    } else {
        n = rnd.next(0LL, MAX_N);
    }

    println(n);
    return 0;
}
