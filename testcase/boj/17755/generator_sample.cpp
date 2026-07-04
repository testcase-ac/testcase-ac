#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

const long long LIMIT = 1000000000000000000LL;

long long digitSquareSum(long long value) {
    long long sum = 0;
    while (value > 0) {
        int digit = value % 10;
        sum += digit * digit;
        value /= 10;
    }
    return sum;
}

long long randLong(long long lo, long long hi) {
    return rnd.next(lo, hi);
}

long long clampToLimit(__int128 value) {
    if (value < 1) return 1;
    if (value > LIMIT) return LIMIT;
    return (long long)value;
}

vector<long long> solutionsForK(long long k) {
    vector<long long> values;
    for (long long s = 1; s <= 1458; ++s) {
        __int128 candidate = (__int128)k * s;
        if (candidate > LIMIT) break;
        long long n = (long long)candidate;
        if (digitSquareSum(n) == s) {
            values.push_back(n);
        }
    }
    return values;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    long long k;
    long long a;
    long long b;

    if (mode == 0) {
        k = randLong(1, 200);
        a = randLong(1, 20000);
        b = min(LIMIT, a + randLong(0, 20000));
    } else if (mode == 1) {
        k = rnd.any(vector<long long>{1, 2, 3, 9, 10, 51, 99, 100, 999});
        vector<long long> values = solutionsForK(k);
        if (!values.empty()) {
            long long center = rnd.any(values);
            long long left = randLong(0, min(center - 1, 5000LL));
            long long right = randLong(0, min(LIMIT - center, 5000LL));
            a = center - left;
            b = center + right;
        } else {
            a = randLong(1, 100000);
            b = min(LIMIT, a + randLong(0, 100000));
        }
    } else if (mode == 2) {
        k = randLong(1, 1000000);
        a = randLong(1, 1000000000);
        b = min(LIMIT, a + randLong(0, 50));
    } else if (mode == 3) {
        vector<long long> pivots = {
            1LL,
            9LL,
            10LL,
            99LL,
            100LL,
            999LL,
            1000LL,
            999999LL,
            1000000LL,
            999999999999LL,
            1000000000000LL,
            LIMIT,
        };
        long long center = rnd.any(pivots);
        k = rnd.any(vector<long long>{1, 9, 10, 81, 999, 1000000000LL});
        long long radius = randLong(0, min(100000LL, max(center - 1, LIMIT - center)));
        a = max(1LL, center - radius);
        b = clampToLimit((__int128)center + randLong(0, 100000));
        if (a > b) swap(a, b);
    } else if (mode == 4) {
        k = randLong(1, LIMIT);
        a = randLong(max(1LL, LIMIT - 1000000), LIMIT);
        b = randLong(a, LIMIT);
    } else {
        k = randLong(1, LIMIT / 1458);
        long long s = randLong(1, 1458);
        long long base = clampToLimit((__int128)k * s);
        long long width = randLong(0, 1000000);
        a = max(1LL, base - randLong(0, min(width, base - 1)));
        b = min(LIMIT, base + randLong(0, width));
    }

    println(k, a, b);
    return 0;
}
