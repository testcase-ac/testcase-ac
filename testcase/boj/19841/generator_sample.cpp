#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const long long LIMIT = 100000000000LL;

long long clampValue(long long x) {
    return max(1LL, min(LIMIT, x));
}

long long randomNoZeroNumber(int length) {
    long long value = 0;
    for (int i = 0; i < length; ++i) {
        value = value * 10 + rnd.next(1, 9);
    }
    return value;
}

long long randomPowerOfTen() {
    vector<long long> powers;
    for (long long p = 1; p <= LIMIT; p *= 10) {
        powers.push_back(p);
        if (p == LIMIT) break;
    }
    return rnd.any(powers);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long a = 1;
    long long b = 1;
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        a = rnd.next(1LL, 200LL);
        b = rnd.next(a, min(LIMIT, a + rnd.next(0LL, 300LL)));
    } else if (mode == 1) {
        long long center = rnd.any(vector<long long>{1LL, 2LL, 3LL, 5LL, 7LL, 13LL, 83LL, 283LL, LIMIT});
        long long radius = rnd.next(0LL, 1000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
    } else if (mode == 2) {
        long long center = randomPowerOfTen();
        long long radius = rnd.next(0LL, 2000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
    } else if (mode == 3) {
        int length = rnd.next(1, 11);
        long long center = randomNoZeroNumber(length);
        long long radius = rnd.next(0LL, 5000LL);
        a = clampValue(center - rnd.next(0LL, radius));
        b = clampValue(center + rnd.next(0LL, radius));
    } else if (mode == 4) {
        long long block = rnd.next(1LL, LIMIT / 1000LL);
        a = clampValue(block * 1000LL);
        b = clampValue(a + rnd.next(0LL, 999LL));
    } else {
        a = rnd.next(1LL, LIMIT);
        long long width = rnd.next(0LL, 1000000LL);
        b = clampValue(a + width);
    }

    if (a > b) swap(a, b);
    println(a, b);
    return 0;
}
