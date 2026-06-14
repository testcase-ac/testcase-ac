#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

using int64 = long long;

const int64 MIN_N = 2;
const int64 MAX_N = 100000000000000LL;

int64 clampN(int64 x) {
    return max(MIN_N, min(MAX_N, x));
}

int64 boundedPow(int64 base, int exp) {
    __int128 value = 1;
    for (int i = 0; i < exp; ++i) {
        value *= base;
        if (value > MAX_N) return MAX_N;
    }
    return (int64)value;
}

int64 randomPrimePower() {
    vector<int64> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
        31, 37, 41, 43, 47, 53, 97, 101, 997,
        1009, 10007, 99991, 1000003
    };

    int64 p = rnd.any(primes);
    int maxExp = 1;
    __int128 value = p;
    while (value * p <= MAX_N) {
        value *= p;
        ++maxExp;
    }

    int exp = rnd.next(2, max(2, maxExp));
    return boundedPow(p, exp);
}

int64 randomN() {
    int mode = rnd.next(8);
    if (mode == 0) {
        return rnd.next(MIN_N, 30LL);
    }
    if (mode == 1) {
        return rnd.next(31LL, 10000LL);
    }
    if (mode == 2) {
        return rnd.next(MAX_N - 1000000LL, MAX_N);
    }
    if (mode == 3) {
        vector<int64> anchors = {2, 3, 4, 8, 9, 16, 25, 27, 32, 49, 64, 81, 121, MAX_N};
        return rnd.any(anchors);
    }
    if (mode == 4) {
        int64 x = randomPrimePower();
        return clampN(x + rnd.next(-3LL, 3LL));
    }
    if (mode == 5) {
        int64 root = rnd.next(2LL, 10000000LL);
        return clampN(root * root + rnd.next(-2LL, 2LL));
    }
    if (mode == 6) {
        int64 x = rnd.next(2LL, 100000000LL);
        return clampN(x * rnd.next(2LL, 1000000LL));
    }
    return rnd.next(MIN_N, MAX_N);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 24);
    println(t);
    for (int i = 0; i < t; ++i) {
        println(randomN());
    }

    return 0;
}
