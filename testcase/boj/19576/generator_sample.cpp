#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long boundedPower(long long base, int exponent) {
    long long value = 1;
    for (int i = 0; i < exponent; ++i) {
        if (value > 1000000000LL / base) return 1000000000LL;
        value *= base;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> a;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int n = rnd.next(1, 30);
        long long base = rnd.next(1, 20);
        long long multiplier = rnd.next(2, 6);
        long long value = base;
        for (int i = 0; i < n; ++i) {
            a.push_back(value);
            if (value <= 1000000000LL / multiplier) value *= multiplier;
        }
    } else if (mode == 1) {
        vector<long long> primes = {999999937LL, 999999929LL, 999999893LL, 999999883LL,
                                    999999797LL, 999999761LL, 999999757LL, 999999751LL,
                                    999999739LL, 999999733LL, 999999721LL, 999999677LL};
        shuffle(primes.begin(), primes.end());
        int n = rnd.next(2, (int)primes.size());
        a.assign(primes.begin(), primes.begin() + n);
        if (rnd.next(0, 1)) a.push_back(1);
    } else if (mode == 2) {
        int chains = rnd.next(2, 5);
        for (int c = 0; c < chains; ++c) {
            long long base = rnd.next(2, 35) * (long long)rnd.next(2, 35);
            int len = rnd.next(2, 7);
            long long value = base;
            for (int i = 0; i < len; ++i) {
                a.push_back(value);
                int multiplier = rnd.next(2, 5);
                if (value <= 1000000000LL / multiplier) value *= multiplier;
            }
        }
    } else if (mode == 3) {
        int n = rnd.next(5, 35);
        vector<long long> pool = {1, 2, 3, 4, 6, 8, 9, 12, 18, 24, 27, 36,
                                  72, 81, 108, 216, 1000000000LL};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 4) {
        int n = rnd.next(3, 25);
        long long anchor = rnd.next(2, 1000);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 2) == 0) {
                a.push_back(anchor * rnd.next(1LL, 1000000000LL / anchor));
            } else {
                a.push_back(rnd.next(1, 1000000000));
            }
        }
    } else {
        int n = rnd.next(2, 24);
        long long base = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            int exponent = rnd.next(0, 12);
            long long value = boundedPower(base, exponent);
            if (value == 1000000000LL) value = rnd.next(1, 1000000000);
            a.push_back(value);
        }
    }

    shuffle(a.begin(), a.end());
    println((int)a.size());
    println(a);

    return 0;
}
