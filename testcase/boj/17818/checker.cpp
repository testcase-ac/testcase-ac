#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using ull = unsigned long long;

ll A, B;

// Multiply a and b modulo mod safely
ull mul_mod(ull a, ull b, ull mod) {
    __uint128_t z = ( __uint128_t ) a * b;
    return (ull)(z % mod);
}

// Fast exponentiation modulo mod
ull pow_mod(ull a, ull d, ull mod) {
    ull res = 1;
    while (d) {
        if (d & 1) res = mul_mod(res, a, mod);
        a = mul_mod(a, a, mod);
        d >>= 1;
    }
    return res;
}

// Deterministic Miller–Rabin for 64-bit integers
bool isPrimeLL(ull n) {
    if (n < 2) return false;
    // small primes
    for (ull p: {2ULL,3ULL,5ULL,7ULL,11ULL,13ULL,17ULL,19ULL,23ULL,29ULL,31ULL,37ULL}) {
        if (n % p == 0) return n == p;
    }
    ull d = n - 1, s = 0;
    while (!(d & 1)) {
        d >>= 1;
        s++;
    }
    for (ull a: {2ULL, 325ULL, 9375ULL, 28178ULL, 450775ULL, 9780504ULL, 1795265022ULL}) {
        if (a % n == 0) continue;
        ull x = pow_mod(a, d, n);
        if (x == 1 || x == n - 1) continue;
        bool composite = true;
        for (ull r = 1; r < s; r++) {
            x = mul_mod(x, x, n);
            if (x == n - 1) {
                composite = false;
                break;
            }
        }
        if (composite) return false;
    }
    return true;
}

// Reads and checks an answer (either jury's or contestant's)
vector<ll> readAns(InStream &stream) {
    vector<ll> seq;
    // First number is either -1 (impossible) or k = length of sequence
    ll k = stream.readLong(-1LL, 1000LL, "length");
    if (k == -1) {
        // must be exactly "-1" and nothing else
        stream.readEof();
        return seq;  // empty => "no solution"
    }
    // Otherwise we expect a sequence of length k
    if (k < 2 || k > 30) {
        stream.quitf(_wa, "length of sequence should be between 2 and 30, found %lld", k);
    }
    seq.resize(k);
    for (int i = 0; i < k; i++) {
        ll x = stream.readLong(2LL, (ll)1e15, format("a[%d]", i).c_str());
        if (!isPrimeLL((ull)x)) {
            stream.quitf(_wa, "a[%d] = %lld is not prime", i, x);
        }
        seq[i] = x;
    }
    // no extra tokens
    stream.readEof();
    // Check endpoints
    if (seq.front() != A) {
        stream.quitf(_wa, "sequence should start with A = %lld, found %lld", A, seq.front());
    }
    if (seq.back() != B) {
        stream.quitf(_wa, "sequence should end with B = %lld, found %lld", B, seq.back());
    }
    // Check neighbor differences are prime
    for (int i = 0; i + 1 < k; i++) {
        ll d = llabs(seq[i] - seq[i+1]);
        if (d <= 1 || !isPrimeLL((ull)d)) {
            stream.quitf(_wa,
                "abs(a[%d] - a[%d]) = |%lld - %lld| = %lld is not prime",
                i, i+1, seq[i], seq[i+1], d);
        }
    }
    return seq;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // Read input
    A = inf.readLong();
    B = inf.readLong();
    // Read jury and participant answers
    auto jres = readAns(ans);
    auto pres = readAns(ouf);

    // If jury says impossible
    if (jres.empty()) {
        if (!pres.empty()) {
            quitf(_wa, "solution does not exist, but participant output a sequence of length %d",
                  (int)pres.size());
        } else {
            quitf(_ok, "correctly found no solution");
        }
    } else {
        // solution exists
        if (pres.empty()) {
            quitf(_wa, "solution exists, but participant output -1");
        } else {
            quitf(_ok, "correct sequence of length %d", (int)pres.size());
        }
    }
    return 0;
}
