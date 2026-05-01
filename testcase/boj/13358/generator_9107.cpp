#include "testlib.h"
using namespace std;

long long gcdll(long long a, long long b) {
    while (b) {
        long long t = a % b;
        a = b;
        b = t;
    }
    return a;
}

long long randomNGeneral() {
    // Bias towards small values, but sometimes large
    int mode = rnd.next(0, 2);
    if (mode == 0) return rnd.next(1, 20);           // very small
    if (mode == 1) return rnd.next(1, 1000000);      // medium
    return rnd.next(1, 1000000000);                  // large
}

int buildCompositeLikeM() {
    // Build a number with small prime factors, typically composite
    vector<int> primes = {2, 3, 5, 7, 11};
    long long m = 1;
    for (int p : primes) {
        int k = rnd.next(0, 3); // exponent 0..3
        for (int i = 0; i < k; i++) {
            if (m * p > 1000000000LL) break;
            m *= p;
        }
    }
    if (m == 1) m = 6; // ensure >1 and composite
    return (int)m;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    long long n = 0, m = 0;

    int type = rnd.next(0, 9);

    switch (type) {
        case 0: {
            // Hand-picked small / sample-like cases
            vector<pair<int,int>> cand = {
                {1, 1},
                {1, 2},
                {2, 1},
                {2, 2},
                {3, 1},
                {3, 2},
                {5, 123456789}, // sample 2
                {94, 265},      // sample 3
                {2, 42}         // sample 1
            };
            auto p = rnd.any(cand);
            n = p.first;
            m = p.second;
            break;
        }
        case 1: {
            // m = 1, arbitrary n (answer is always 0)
            n = rnd.next(1, 1000000000);
            m = 1;
            break;
        }
        case 2: {
            // Prime modulus
            vector<int> primes = {
                2, 3, 5, 7, 11, 13, 17, 19,
                97, 101, 9973, 99991, 999983, 999999937
            };
            m = rnd.any(primes);
            n = randomNGeneral();
            break;
        }
        case 3: {
            // Power of two modulus
            int maxK = 0;
            while ((1LL << (maxK + 1)) <= 1000000000LL) maxK++;
            int k = rnd.next(0, maxK); // 2^0 .. 2^maxK
            m = 1LL << k;
            n = randomNGeneral();
            break;
        }
        case 4: {
            // Prime power modulus p^k
            vector<int> primes = {3, 5, 7};
            int p = rnd.any(primes);
            long long cur = 1;
            int maxK = 0;
            while (cur * p <= 1000000000LL) {
                cur *= p;
                maxK++;
            }
            int k = rnd.next(1, maxK);
            cur = 1;
            for (int i = 0; i < k; i++) cur *= p;
            m = cur;
            n = randomNGeneral();
            break;
        }
        case 5: {
            // Highly composite-like modulus
            m = buildCompositeLikeM();
            n = randomNGeneral();
            break;
        }
        case 6: {
            // Small n (tower not too tall), arbitrary m
            n = rnd.next(1, 8);
            // Bias m a little towards special small values
            int mode = rnd.next(0, 3);
            if (mode == 0) {
                vector<int> smallMs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
                m = rnd.any(smallMs);
            } else {
                m = rnd.next(1, 1000000000);
            }
            break;
        }
        case 7: {
            // n close to m
            m = rnd.next(2, 1000000000);
            int delta = rnd.next(-5, 5);
            long long candN = (long long)m + delta;
            if (candN < 1) candN = 1;
            if (candN > 1000000000LL) candN = 1000000000LL;
            n = candN;
            break;
        }
        case 8: {
            // gcd(n, m) = 1
            m = buildCompositeLikeM();
            do {
                n = randomNGeneral();
            } while (gcdll(n, m) != 1);
            break;
        }
        case 9: {
            // gcd(n, m) > 1
            m = buildCompositeLikeM();
            vector<int> pf;
            for (int p : {2,3,5,7,11}) {
                if (m % p == 0) pf.push_back(p);
            }
            if (pf.empty()) {
                // Fallback: force a small factor
                if (m * 2 <= 1000000000) m *= 2;
                pf.push_back(2);
            }
            int p = rnd.any(pf);
            long long maxK = 1000000000LL / p;
            long long k = rnd.next(1LL, maxK);
            n = k * p;
            break;
        }
        default: {
            n = 5;
            m = 123456789;
        }
    }

    println((int)n, (int)m);
    return 0;
}
