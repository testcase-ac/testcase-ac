#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;
using int64 = long long;

const int64 LIMIT = 999999999999LL;

int64 powLimited(int64 base, int exp) {
    int64 value = 1;
    for (int i = 0; i < exp; ++i) {
        if (value > LIMIT / base) break;
        value *= base;
    }
    return value;
}

int64 buildFromExponents(vector<int64> primes, vector<int> exponents) {
    int64 value = 1;
    for (int i = 0; i < (int)primes.size(); ++i) {
        for (int j = 0; j < exponents[i]; ++j) {
            if (value > LIMIT / primes[i]) return value;
            value *= primes[i];
        }
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int64> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
        37, 41, 43, 47
    };
    vector<int64> largePrimes = {
        999983, 999979, 999961, 999953, 999931, 999917, 999907
    };
    vector<int64> values;

    int t = rnd.next(12, 40);
    values.reserve(t);

    for (int caseId = 0; caseId < t; ++caseId) {
        int mode = rnd.next(0, 7);
        int64 n = 2;

        if (mode == 0) {
            n = rnd.any(smallPrimes);
        } else if (mode == 1) {
            int64 p = rnd.any(smallPrimes);
            int maxExp = 1;
            int64 cur = p;
            while (cur <= LIMIT / p) {
                cur *= p;
                ++maxExp;
            }
            n = powLimited(p, rnd.next(1, min(maxExp, 20)));
        } else if (mode == 2) {
            vector<int64> primes = smallPrimes;
            shuffle(primes.begin(), primes.end());
            int k = rnd.next(2, 5);
            vector<int> exponents(k);
            for (int i = 0; i < k; ++i) exponents[i] = rnd.next(1, 4);
            n = buildFromExponents(vector<int64>(primes.begin(), primes.begin() + k), exponents);
        } else if (mode == 3) {
            vector<int64> primes = smallPrimes;
            shuffle(primes.begin(), primes.end());
            int k = rnd.next(2, 4);
            vector<int> exponents(k, 1);
            exponents[0] = rnd.next(5, 12);
            n = buildFromExponents(vector<int64>(primes.begin(), primes.begin() + k), exponents);
        } else if (mode == 4) {
            vector<int64> primes = smallPrimes;
            shuffle(primes.begin(), primes.end());
            int k = rnd.next(4, 9);
            vector<int> exponents(k, 1);
            n = buildFromExponents(vector<int64>(primes.begin(), primes.begin() + k), exponents);
        } else if (mode == 5) {
            int64 p = rnd.any(largePrimes);
            int64 q = rnd.any(largePrimes);
            n = p * q;
            if (n > LIMIT) n = p;
        } else if (mode == 6) {
            int64 p = rnd.any(largePrimes);
            int64 q = rnd.any(smallPrimes);
            int extra = rnd.next(1, 4);
            n = p;
            for (int i = 0; i < extra && n <= LIMIT / q; ++i) n *= q;
        } else {
            int64 base = rnd.next(2LL, 1000000LL);
            n = max(2LL, base * rnd.next(2LL, 999999LL));
            while (n > LIMIT) n /= rnd.next(2LL, 9LL);
        }

        values.push_back(max(2LL, min(n, LIMIT)));
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    for (int64 value : values) println(value);

    return 0;
}
