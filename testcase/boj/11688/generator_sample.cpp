#include "testlib.h"
#include <algorithm>
#include <numeric>
#include <vector>
using namespace std;

long long powLimited(long long base, int exp) {
    long long value = 1;
    for (int i = 0; i < exp; ++i) value *= base;
    return value;
}

long long randomSmooth(long long limit, int maxExp) {
    vector<int> primes = {2, 3, 5, 7, 11, 13};
    long long value = 1;
    for (int p : primes) {
        int exp = rnd.next(0, maxExp);
        long long mult = powLimited(p, exp);
        while (value * mult > limit && exp > 0) {
            --exp;
            mult /= p;
        }
        value *= mult;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxA = 1000000;
    const long long maxL = 1000000000000LL;
    int mode = rnd.next(0, 5);

    long long a = 1;
    long long b = 1;
    long long L = 1;

    if (mode == 0) {
        a = rnd.next(1, 40);
        b = rnd.next(1, 40);
        long long base = lcm(a, b);
        L = base * rnd.next(1, (int)min(1000LL, maxL / base));
    } else if (mode == 1) {
        a = randomSmooth(maxA, 6);
        b = randomSmooth(maxA, 6);
        long long base = lcm(a, b);
        L = base * rnd.next(1, (int)min(1000LL, maxL / base));
    } else if (mode == 2) {
        a = rnd.next(1, 2000);
        b = rnd.next(1, 2000);
        long long base = lcm(a, b);
        L = base * rnd.next(1, (int)min(1000LL, maxL / base));
        int p = rnd.any(vector<int>{2, 3, 5, 7, 11});
        while (L % p == 0) L /= p;
        if (L == 0) L = 1;
    } else if (mode == 3) {
        long long common = randomSmooth(1000, 4);
        a = common * rnd.next(1, (int)(maxA / common));
        b = common * rnd.next(1, (int)(maxA / common));
        long long base = lcm(a, b);
        L = base * rnd.next(1, (int)min(20LL, maxL / base));
    } else if (mode == 4) {
        a = rnd.next(900000, 1000000);
        b = rnd.next(900000, 1000000);
        long long base = lcm(a, b);
        L = base <= maxL ? base : rnd.next(1LL, maxL);
    } else {
        vector<long long> values = {1, 2, 3, 6, 30, 40, 720, 999999, 1000000};
        a = rnd.any(values);
        b = rnd.any(values);
        L = rnd.any(values);
        if (rnd.next(0, 1)) L *= rnd.next(1, 1000);
        L = min(L, maxL);
    }

    println(a, b, L);
    return 0;
}
