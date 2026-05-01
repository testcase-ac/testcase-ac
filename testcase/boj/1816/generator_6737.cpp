#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ull = unsigned long long;
using u128 = __uint128_t;

// Miller-Rabin for 64-bit
ull mod_mul(ull a, ull b, ull mod) {
    u128 r = (u128)a * b;
    return (ull)(r % mod);
}
ull mod_pow(ull a, ull d, ull mod) {
    ull r = 1;
    while (d) {
        if (d & 1) r = mod_mul(r, a, mod);
        a = mod_mul(a, a, mod);
        d >>= 1;
    }
    return r;
}
bool isPrime(ull n) {
    if (n < 2) return false;
    for (ull p : {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL})
        if (n == p) return true;
        else if (n % p == 0) return n == p;
    ull d = n - 1, s = 0;
    while ((d & 1) == 0) { d >>= 1; s++; }
    for (ull a : {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = mod_pow(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool comp = true;
        for (ull r = 1; r < s; r++) {
            x = mod_mul(x, x, n);
            if (x == n - 1) { comp = false; break; }
        }
        if (comp) return false;
    }
    return true;
}

// generate a random prime in [lo, hi]
ull nextPrime(ull lo, ull hi) {
    while (true) {
        ull x = rnd.next(lo, hi);
        if ((x & 1) == 0) x++;
        if (x > hi) continue;
        for (ull y = x; y <= hi; y += 2) {
            if (isPrime(y)) return y;
        }
    }
}

// sieve small primes up to MAXP
vector<int> sievePrimes(int MAXP) {
    vector<bool> is(MAXP+1, true);
    is[0]=is[1]=false;
    for(int i=2;i*i<=MAXP;i++) if(is[i])
        for(int j=i*i;j<=MAXP;j+=i) is[j]=false;
    vector<int> ps;
    for(int i=2;i<=MAXP;i++) if(is[i]) ps.push_back(i);
    return ps;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // generate N values
    int N = rnd.next(1, 10);
    vector<ull> S;
    // small primes for NO-case
    vector<int> smallPrimes = sievePrimes(10000); // primes <=1e4
    for (int i = 0; i < N; i++) {
        int tp = rnd.next(0, 2); // 0=NO,1=YES composite,2=YES square
        if (tp == 0) {
            // NO: has a small prime factor <=1e6 (we use <=1e4)
            int p = rnd.any(smallPrimes);
            // choose k so that S = p*k in [1e12,1e18]
            ull lo = (1000000000000ULL + p - 1) / p;
            ull hi = 1000000000000000000ULL / p;
            ull k = rnd.next(lo, hi);
            ull val = (ull)k * p;
            S.push_back(val);
        } else if (tp == 1) {
            // YES composite: product of two primes >1e6
            ull p1, p2;
            do {
                p1 = nextPrime(1000001ULL, 1000000000ULL);
                p2 = nextPrime(1000001ULL, 1000000000ULL);
                u128 prod = (u128)p1 * p2;
                if (prod >= 1000000000000ULL && prod <= 1000000000000000000ULL)
                    break;
            } while (true);
            S.push_back((ull)((u128)p1 * p2));
        } else {
            // YES square: square of a prime >1e6
            ull p;
            do {
                p = nextPrime(1000001ULL, 1000000000ULL);
                u128 sq = (u128)p * p;
                if (sq >= 1000000000000ULL && sq <= 1000000000000000000ULL)
                    break;
            } while (true);
            S.push_back((ull)((u128)p * p));
        }
    }
    // shuffle order for variability
    shuffle(S.begin(), S.end());
    // output
    println(N);
    for (ull v : S) println(v);
    return 0;
}
