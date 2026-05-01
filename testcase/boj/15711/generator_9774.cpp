#include "testlib.h"
using namespace std;

typedef unsigned long long ull;
typedef __uint128_t u128;

ull mod_mul(ull a, ull b, ull mod) {
    return (u128)a * b % mod;
}

ull mod_pow(ull a, ull d, ull mod) {
    ull r = 1 % mod;
    while (d) {
        if (d & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        d >>= 1;
    }
    return r;
}

bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n == p) return true;
        if (n % p == 0) return false;
    }
    ull d = n - 1;
    int s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = mod_pow(a % n, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (int r = 1; r < s; ++r) {
            x = mod_mul(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

pair<long long, long long> makeFromSum(ull S) {
    const long long LIM = 2000000000000LL;
    long long s = (long long)S;
    long long minA = max(1LL, s - LIM);
    long long maxA = min(LIM, s - 1);
    long long A = rnd.next(minA, maxA);
    long long B = s - A;
    return make_pair(A, B);
}

// Generate odd S such that S-2 is prime (wantPrime=true) or composite (wantPrime=false)
ull genS_from_P(bool wantPrime) {
    const ull maxP = 3999999999997ULL; // so that P+2 <= 4e12 - 1
    while (true) {
        long long Pl = rnd.next(3LL, (long long)maxP);
        ull P = (ull)Pl;
        if ((P & 1ULL) == 0) P++; // make it odd, stays within range
        bool isp = isPrime(P);
        if (wantPrime && isp) return P + 2;
        if (!wantPrime && !isp) return P + 2;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIM = 2000000000000LL;
    vector<pair<long long, long long>> tests;

    // Small edge and typical cases
    tests.push_back({1, 1}); // S = 2, NO
    tests.push_back({1, 2}); // S = 3, NO
    tests.push_back({1, 3}); // S = 4, YES
    tests.push_back({2, 2}); // S = 4, YES
    tests.push_back({2, 3}); // S = 5, YES (2+3)
    tests.push_back({3, 4}); // S = 7, YES
    tests.push_back({4, 4}); // S = 8, YES

    // Small odd S where S-2 is composite -> NO (11 = 2+9, 3+8, 5+6)
    tests.push_back({2, 9}); // S = 11, NO
    // Another small odd S where S-2 is prime -> YES (13 = 2+11)
    tests.push_back({5, 8}); // S = 13, YES

    // Max boundary even sum
    tests.push_back({LIM, LIM}); // S = 4e12, large even

    // Large odd with S-2 prime (YES case)
    ull S_prime = genS_from_P(true);
    tests.push_back(makeFromSum(S_prime));

    // Large odd with S-2 composite (NO case)
    ull S_comp = genS_from_P(false);
    tests.push_back(makeFromSum(S_comp));

    // A few additional random cases for variability
    int extra = rnd.next(0, 3);
    for (int i = 0; i < extra; ++i) {
        int type = rnd.next(0, 3);
        if (type == 0) {
            // Small random
            long long A = rnd.next(1LL, 20LL);
            long long B = rnd.next(1LL, 20LL);
            tests.push_back({A, B});
        } else if (type == 1) {
            // Random even sum, moderate size
            long long S = rnd.next(4LL, 1000000LL);
            if (S % 2 == 1) ++S;
            tests.push_back(makeFromSum((ull)S));
        } else if (type == 2) {
            // Random odd sum, moderate size
            long long S = rnd.next(5LL, 1000000LL);
            if (S % 2 == 0) ++S;
            tests.push_back(makeFromSum((ull)S));
        } else {
            // Near upper limit random
            long long A = rnd.next(LIM - 1000, LIM);
            long long B = rnd.next(LIM - 1000, LIM);
            tests.push_back({A, B});
        }
    }

    println((int)tests.size());
    for (auto &p : tests)
        println(p.first, p.second);

    return 0;
}
