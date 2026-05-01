#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 1000000000000LL;
    long long k = 2;

    int mode = rnd.next(0, 8);

    vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41};

    if (mode == 0) {
        // Completely random in full range
        k = rnd.next(2LL, LIM);
    } else if (mode == 1) {
        // Small k, easy to factor by hand
        k = rnd.next(2, 1000);
    } else if (mode == 2) {
        // Product of small primes with random exponents
        k = 1;
        int L = rnd.next(1, 8);
        for (int i = 0; i < L; ++i) {
            int p = rnd.any(smallPrimes);
            int e = rnd.next(1, 4);
            for (int j = 0; j < e; ++j) {
                if (k > LIM / p) break;
                k *= p;
            }
        }
        if (k < 2) k = 2;
    } else if (mode == 3) {
        // Pure prime power
        int p = rnd.any(smallPrimes);
        long long cur = 1;
        int maxE = 0;
        while (cur <= LIM / p) {
            cur *= p;
            ++maxE;
        }
        if (maxE == 0) {
            k = p;
        } else {
            int e = rnd.next(1, maxE);
            cur = 1;
            for (int i = 0; i < e; ++i) cur *= p;
            k = cur;
        }
    } else if (mode == 4) {
        // Power of two times a random odd factor
        int a = rnd.next(1, 39); // 2^39 < 1e12 < 2^40
        long long base = 1LL << a;
        long long maxQ = LIM / base;
        long long q = 1;
        if (maxQ >= 3) {
            // pick random odd in [1, maxQ]
            while (true) {
                q = rnd.next(1LL, maxQ);
                if (q % 2 == 1) break;
            }
        }
        k = base * q;
        if (k < 2) k = 2;
    } else if (mode == 5) {
        // Handpicked near-limit and tricky numbers
        vector<long long> special = {
            1000000000000LL,
            999999999999LL,
            999999999997LL,
            999999999989LL,
            999999996001LL, // 999,998^2 + something, composite-ish
            999983LL,
            999979LL,
            9999991LL
        };
        k = rnd.any(special);
    } else if (mode == 6) {
        // Perfect square
        long long n = rnd.next(2LL, 1000000LL); // n^2 <= 1e12
        k = n * n;
    } else if (mode == 7) {
        // Handpicked small to medium interesting values
        vector<long long> specialSmall = {
            2, 3, 4, 6, 8, 9, 10, 12, 18, 36, 72, 100, 360,
            720, 840, 1024, 1728, 999983, 999999937LL
        };
        k = rnd.any(specialSmall);
    } else if (mode == 8) {
        // Heavily composite-ish: mix of small primes with higher exponents
        k = 1;
        vector<int> primes = {2, 3, 5, 7, 11};
        for (int p : primes) {
            long long maxLimit = LIM / k;
            long long cur = 1;
            int maxE = 0;
            while (cur <= maxLimit / p) {
                cur *= p;
                ++maxE;
            }
            if (maxE <= 0) continue;
            int e;
            if (rnd.next(0, 3) == 0) e = maxE;          // sometimes use max exponent
            else e = rnd.next(0, maxE);                 // sometimes smaller or zero
            cur = 1;
            for (int i = 0; i < e; ++i) cur *= p;
            k *= cur;
        }
        if (k < 2) k = 2;
    }

    // Final safety clamp
    if (k < 2) k = 2;
    if (k > LIM) k = LIM;

    println(k);
    return 0;
}
