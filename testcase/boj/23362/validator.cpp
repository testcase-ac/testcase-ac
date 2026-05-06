#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using u64 = unsigned long long;
using u128 = __uint128_t;

// Multiply a and b under modulo mod, safe for 64-bit
u64 mul_mod(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
}

// Fast exponentiation under modulo
u64 power_mod(u64 a, u64 d, u64 mod) {
    u64 res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return res;
}

// Miller–Rabin primality test for 64-bit integers
bool isPrime(u64 n) {
    if (n < 2) return false;
    // small primes trial
    for (u64 p : {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
        if (n % p == 0) return n == p;
    }
    // write n-1 = d * 2^s
    u64 d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1;
        ++s;
    }
    // bases enough for testing 64-bit
    for (u64 a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        u64 x = power_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (u64 r = 1; r < s; ++r) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

// Pollard's Rho algorithm for finding a non-trivial factor
mt19937_64 rng(chrono::high_resolution_clock::now().time_since_epoch().count());

u64 pollards_rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    uniform_int_distribution<u64> distC(1, n - 1);
    uniform_int_distribution<u64> distX(0, n - 1);
    while (true) {
        u64 c = distC(rng);
        u64 x = distX(rng);
        u64 y = x;
        u64 d = 1;
        while (d == 1) {
            x = (mul_mod(x, x, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            y = (mul_mod(y, y, n) + c) % n;
            u64 diff = x > y ? x - y : y - x;
            d = std::gcd(diff, n);
            if (d == n) break;
        }
        if (d > 1 && d < n) return d;
        // retry on failure
    }
}

// Factor n into prime factors (recursively) and count them in mp
void factor(u64 n, map<u64,int> &mp) {
    if (n == 1) return;
    if (isPrime(n)) {
        mp[n]++;
    } else {
        u64 d = pollards_rho(n);
        factor(d, mp);
        factor(n / d, mp);
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases
    int T = inf.readInt(1, 60, "T");
    inf.readEoln();

    // For each test case, there must be a blank line, then N
    for (int tc = 1; tc <= T; ++tc) {
        // blank line
        string blank = inf.readLine("[^]*", "blank");
        ensuref(blank.empty(), "Line before test case %d is not blank", tc);

        // read N
        // 1 <= N < 10^14  => N <= 10^14 - 1 = 99999999999999
        long long N = inf.readLong(1LL, 100000000000000LL - 1, "N");
        inf.readEoln();

        // Validate the condition "N has at most 47 divisors"
        map<u64,int> mp;
        factor((u64)N, mp);
        // compute divisor count
        long long divs = 1;
        for (auto &pe : mp) {
            divs = divs * (pe.second + 1);
            // avoid overflow though divs stays small
            ensuref(divs <= (long long)1e9, "Overflow in divisor count for N=%lld", N);
        }
        ensuref(divs <= 47, "N=%lld has too many divisors: %lld > 47", N, divs);
    }

    inf.readEof();
    return 0;
}
