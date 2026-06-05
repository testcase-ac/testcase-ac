#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

long long digitSum(long long x) {
    long long sum = 0;
    while (x > 0) {
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

long long clampInput(long long x) {
    return max(1LL, min(1000000000000000000LL, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000000000000LL;
    const vector<long long> powers = {
        1LL,
        10LL,
        100LL,
        1000LL,
        10000LL,
        100000LL,
        1000000LL,
        10000000LL,
        100000000LL,
        1000000000LL,
        10000000000LL,
        100000000000LL,
        1000000000000LL,
        10000000000000LL,
        100000000000000LL,
        1000000000000000LL,
        10000000000000000LL,
        100000000000000000LL,
        LIMIT,
    };

    long long n;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        n = rnd.next(1LL, 500LL);
    } else if (mode == 1) {
        long long base = rnd.any(powers);
        long long delta = rnd.next(-200LL, 200LL);
        n = clampInput(base + delta);
    } else if (mode == 2) {
        long long m = rnd.next(1LL, LIMIT - 200LL);
        n = m + digitSum(m);
    } else if (mode == 3) {
        long long base = rnd.next(1LL, 1000000000LL);
        long long scale = rnd.any(powers);
        n = clampInput(base * min(scale, 1000000000LL) + rnd.next(0LL, 200LL));
    } else if (mode == 4) {
        n = rnd.next(LIMIT - 1000LL, LIMIT);
    } else {
        n = rnd.next(1LL, LIMIT);
    }

    println(n);
    return 0;
}
