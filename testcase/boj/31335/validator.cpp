#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using int64 = long long;
using i128 = __int128_t;
const long long MAXN = (long long)1e18;

// multiply with overflow check, returns (a*b) but if > limit, returns limit+1
long long safeMul(long long a, long long b, long long limit) {
    if (a == 0 || b == 0) return 0;
    if (a > limit / b) return limit + 1;
    return a * b;
}

// power with overflow check, returns min(base^exp, limit+1)
long long safePow(long long base, int exp, long long limit) {
    long long res = 1;
    while (exp > 0 && res <= limit) {
        if (exp & 1) {
            res = safeMul(res, base, limit);
            if (res > limit) return limit + 1;
        }
        exp >>= 1;
        if (exp) {
            base = safeMul(base, base, limit);
            if (base > limit) base = limit + 1;
        }
    }
    return res;
}

// factorize using trial division up to cube root (sufficient for 1e18 here)
vector<pair<long long,int>> factorize(long long n) {
    vector<pair<long long,int>> f;
    for (long long p = 2; p * p * p <= n; ++p) {
        if (n % p == 0) {
            int cnt = 0;
            while (n % p == 0) {
                n /= p;
                ++cnt;
            }
            f.push_back({p, cnt});
        }
    }
    if (n > 1) {
        // now n is 1, prime, or product of two primes
        long long r = sqrtl((long double)n);
        while ((r+1)*(r+1) <= n) ++r;
        while (r*r > n) --r;
        if (r > 1 && r * r == n) {
            // n = p^2
            f.push_back({r, 2});
        } else {
            // n is prime or product of two primes
            // if product of two primes p*q, we treat both as exponent 1; that’s fine.
            // We don't actually need exponents of factors of a, only primes of a.
            // But to be consistent, keep single prime n with exp 1.
            f.push_back({n, 1});
        }
    }
    return f;
}

// generate all divisors of a from factorization (primes only matter)
void genDivisorsRec(const vector<long long> &pr, const vector<int> &mx,
                    int idx, long long cur, vector<long long> &divs) {
    if (idx == (int)pr.size()) {
        divs.push_back(cur);
        return;
    }
    long long v = cur;
    for (int e = 0; e <= mx[idx]; ++e) {
        genDivisorsRec(pr, mx, idx+1, v, divs);
        if (e == mx[idx]) break;
        v = safeMul(v, pr[idx], MAXN);
        if (v > MAXN) break;
    }
}

// compute smallest version > a with same prime set, <= N; return -1 if none
long long nextVersion(long long a, long long N) {
    auto f = factorize(a);
    // extract distinct primes
    vector<long long> primes;
    vector<int> maxE;
    for (auto &pp : f) {
        primes.push_back(pp.first);
        maxE.push_back(pp.second);
    }
    // generate all divisors of a to know possible exponents k_i>=1 (since p_i^{k_i} divides a)
    vector<long long> divisors;
    genDivisorsRec(primes, maxE, 0, 1, divisors);
    sort(divisors.begin(), divisors.end());
    divisors.erase(unique(divisors.begin(), divisors.end()), divisors.end());

    // precompute, for each prime p, the list of allowed exponents >=1: all e such that p^e divides a
    int m = (int)primes.size();
    vector<vector<int>> allowed(m);
    for (int i = 0; i < m; ++i) {
        long long p = primes[i];
        long long x = 1;
        for (int e = 0; ; ++e) {
            if (e >= 1) {
                if (a % x == 0) allowed[i].push_back(e);
            }
            long long nx = safeMul(x, p, a);
            if (nx == 0 || nx > a) break;
            x = nx;
        }
        // sort just in case
        sort(allowed[i].begin(), allowed[i].end());
    }

    // get exponents of a: e_i so that a = prod p_i^{e_i}
    vector<int> curE(m, 0);
    long long tmp = a;
    for (int i = 0; i < m; ++i) {
        while (tmp % primes[i] == 0) {
            tmp /= primes[i];
            ++curE[i];
        }
    }
    // sanity
    ensuref(tmp == 1, "Internal factoring error: remaining factor after factoring a");

    long long best = -1;

    // lexicographic next: find rightmost position where we can increase exponent
    // and set following exponents to minimal (here, 1 is always allowed, because k_i>=1)
    for (int pos = m-1; pos >= 0; --pos) {
        // find current exponent index in allowed[pos]
        auto &vec = allowed[pos];
        auto it = lower_bound(vec.begin(), vec.end(), curE[pos]);
        ensuref(it != vec.end() && *it == curE[pos],
                "Exponent of a not found in allowed list");
        ++it;
        if (it == vec.end()) continue; // cannot increase here

        // create new exponent array
        vector<int> newE = curE;
        newE[pos] = *it;
        for (int j = pos+1; j < m; ++j) newE[j] = 1; // minimal positive

        // compute value, stop if overflow or >N
        long long val = 1;
        bool ok = true;
        for (int i = 0; i < m && ok; ++i) {
            long long p = primes[i];
            int e = newE[i];
            long long pe = safePow(p, e, N);
            if (pe > N) { ok = false; break; }
            val = safeMul(val, pe, N);
            if (val > N) { ok = false; break; }
        }
        if (!ok) continue;
        if (val > a && val <= N) {
            if (best == -1 || val < best) best = val;
        }
    }

    return best;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case, single line with two integers a and N
    long long a = inf.readLong(1LL, MAXN, "a");
    inf.readSpace();
    long long N = inf.readLong(a, MAXN, "N");
    inf.readEoln();

    // Problem guarantees: "Each number from 1 to N is the number of some version
    // of some teleporter." and "Each teleporter has its own set of prime numbers"
    // and the next version (if exists) has same prime set and is ordered
    // lexicographically by exponents. There is no guarantee the next version exists,
    // but if it exists it must be <= N. We validate that any 'next version' with the
    // same prime divisor set (if it exists) actually lies in [1, N]; this is implied
    // by the statement and we compute it to ensure no impossible instance is given.
    long long computedNext = nextVersion(a, N);
    // Nothing further to enforce: if computedNext is -1 or in [1,N], that is fine.
    if (computedNext != -1)
        ensuref(1 <= computedNext && computedNext <= N,
                "Next version computed is out of [1,N] range: %lld", computedNext);

    inf.readEof();
}
