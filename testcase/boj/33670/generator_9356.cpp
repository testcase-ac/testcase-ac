#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    typedef long long ll;

    // Some specially chosen interesting cases (including samples and edge-like)
    vector<pair<int, ll>> special = {
        {3, 29},          // sample
        {4, 1},           // sample
        {4, 2},           // sample
        {4, 3},           // sample
        {10000000, 4},    // sample (max N, small L)
        {1, 1},           // minimal
        {1, 1000000000},  // N=1, max L
        {10000000, 1},    // max N, L=1
        {10000000, 1000000000}, // both near max
        {9999991, 9999991},     // both large and equal (prime-ish)
        {10000000, 999999937},  // max N, huge prime-ish L
        {9999991, 1}
    };

    int mode = rnd.next(0, 9);
    int N;
    ll L;

    switch (mode) {
        case 0: {
            // Pick from special curated cases
            auto p = rnd.any(special);
            N = p.first;
            L = p.second;
            break;
        }
        case 1: {
            // Very small values, easy to brute force/check
            N = rnd.next(1, 6);
            L = rnd.next(1, 10);
            break;
        }
        case 2: {
            // Small N, moderate L
            N = rnd.next(1, 20);
            L = rnd.next(1, 1000);
            break;
        }
        case 3: {
            // N = 1 edge cases with random L
            N = 1;
            // Bias a bit towards small L but allow large too
            if (rnd.next(0, 1) == 0)
                L = rnd.next(1, 1000);
            else
                L = rnd.next(1, 1000000000);
            break;
        }
        case 4: {
            // L = 1 edge cases with random N
            L = 1;
            // Bias between very small and very large N
            int t = rnd.next(0, 2);
            if (t == 0)      N = rnd.next(1, 10);
            else if (t == 1) N = rnd.next(10, 1000);
            else             N = rnd.next(1000000, 10000000);
            break;
        }
        case 5: {
            // Large N, small L (performance-heavy but simple arithmetic)
            N = rnd.next(5000000, 10000000);
            vector<int> smallLs = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20};
            L = rnd.any(smallLs);
            break;
        }
        case 6: {
            // Large N, very large L near upper bound
            N = rnd.next(5000000, 10000000);
            int delta = rnd.next(0, 1000000); // up to 1e6 below 1e9
            L = 1000000000LL - delta;
            if (L < 1) L = 1;
            break;
        }
        case 7: {
            // Moderate N, random L across full range, bias to make NL large
            N = rnd.next(1000, 100000);
            if (rnd.next(0, 1) == 0)
                L = rnd.next(1, 1000000000);
            else {
                // Try to make product N*L large but within limits
                ll maxL = 1000000000LL;
                ll minL = max(1LL, 8000000000LL / N); // around 8e15/N
                if (minL > maxL) minL = 1;
                L = rnd.next((int)minL, (int)maxL);
            }
            break;
        }
        case 8: {
            // Prime-ish or structured N, L
            vector<int> primesSmall = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47};
            vector<int> primesMid   = {9973, 99991, 131071, 262147, 524287};
            vector<int> primesLarge = {999983, 1000003, 1999993, 4999999, 9999991};

            int kind = rnd.next(0, 2);
            if (kind == 0)
                N = rnd.any(primesSmall);
            else if (kind == 1)
                N = rnd.any(primesMid);
            else
                N = rnd.any(primesLarge);

            vector<ll> Lcands = {
                2, 3, 4, 5, 6, 10,
                97, 101, 997, 1009,
                99991LL, 999983LL, 1000003LL, 9999991LL, 999999937LL
            };
            L = rnd.any(Lcands);
            if (L > 1000000000LL) L = 999999937LL; // ensure within bound
            break;
        }
        case 9: {
            // Correlated N and L: multiples or divisors
            N = rnd.next(2, 10000000);
            if (rnd.next(0, 1) == 0) {
                // L is a random multiple of N
                int maxk = (int)(1000000000LL / N);
                if (maxk < 1) maxk = 1;
                int k = rnd.next(1, maxk);
                L = 1LL * N * k;
            } else {
                // L is a random divisor of N
                vector<int> divs;
                for (int i = 1; 1LL * i * i <= N; ++i) {
                    if (N % i == 0) {
                        divs.push_back(i);
                        if (i != N / i) divs.push_back(N / i);
                    }
                }
                L = rnd.any(divs);
            }
            break;
        }
        default: {
            // Fallback (shouldn't happen)
            N = 4;
            L = 1;
            break;
        }
    }

    // Ensure bounds (defensive, though all modes already respect them)
    if (N < 1) N = 1;
    if (N > 10000000) N = 10000000;
    if (L < 1) L = 1;
    if (L > 1000000000LL) L = 1000000000LL;

    println(N, L);
    return 0;
}
