#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using u128 = unsigned __int128;

// multiply a and b mod m safely
ll mulmod(ll a, ll b, ll m) {
    u128 res = (u128)a * b;
    return (ll)(res % m);
}

// power a^e mod m
ll powmod(ll a, ll e, ll m) {
    ll res = 1 % m;
    a %= m;
    while (e) {
        if (e & 1) res = mulmod(res, a, m);
        a = mulmod(a, a, m);
        e >>= 1;
    }
    return res;
}

// deterministic Miller-Rabin for 64-bit
bool isPrimeDet(ll n) {
    if (n < 2) return false;
    for (ll p : {2LL, 3LL, 5LL, 7LL, 11LL, 13LL, 17LL, 19LL, 23LL, 29LL, 31LL, 37LL}) {
        if (n % p == 0) return n == p;
    }
    ll d = n - 1, s = 0;
    while ((d & 1) == 0) {
        d >>= 1; s++;
    }
    // bases for 64-bit determinism
    for (ll a : {2LL, 325LL, 9375LL, 28178LL, 450775LL, 9780504LL, 1795265022LL}) {
        if (a % n == 0) continue;
        ll x = powmod(a, d, n);
        if (x == 1 || x == n-1) continue;
        bool comp = true;
        for (int r = 1; r < s; r++) {
            x = mulmod(x, x, n);
            if (x == n-1) {
                comp = false;
                break;
            }
        }
        if (comp) return false;
    }
    return true;
}

// Pollard's Rho
mt19937_64 rng((unsigned)time(nullptr));
ll pollards_rho(ll n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;
    ll c = uniform_int_distribution<ll>(1, n-1)(rng);
    ll x = uniform_int_distribution<ll>(0, n-1)(rng);
    ll y = x;
    ll d = 1;
    auto f = [&](ll v) { return (mulmod(v, v, n) + c) % n; };
    while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(llabs(x - y), n);
        if (d == n) {
            // retry with new parameters
            return pollards_rho(n);
        }
    }
    return d;
}

// factor n into map<prime, exponent>
void factorRec(ll n, map<ll,int> &mp) {
    if (n == 1) return;
    if (isPrimeDet(n)) {
        mp[n]++;
        return;
    }
    ll d = pollards_rho(n);
    factorRec(d, mp);
    factorRec(n / d, mp);
}

// compute exponent of p in (m)!
ll legendre(ll m, ll p) {
    ll cnt = 0;
    while (m > 0) {
        m /= p;
        cnt += m;
    }
    return cnt;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B
    ll A = inf.readLong(3LL, 1000000000000000000LL, "A");
    inf.readSpace();
    ll B = inf.readLong(3LL, 1000000000000000000LL, "B");
    inf.readEoln();
    ensuref(A < B, "Constraint violated: A (%lld) must be < B (%lld)", A, B);
    ensuref(B - A <= 100, "Constraint violated: B-A (%lld) must be <= 100", B - A);

    // Check that there's at least one key K (odd integer in [A,B] with K^2 not dividing (K-1)!)
    bool found = false;
    for (ll K = A; K <= B; ++K) {
        if (K % 2 == 0) continue;  // only odd K
        // factor K
        map<ll,int> fac;
        factorRec(K, fac);
        // check if K^2 divides (K-1)!
        bool divisible = true;
        ll m = K - 1;
        for (auto &pe : fac) {
            ll p = pe.first;
            int e = pe.second;
            ll cnt = legendre(m, p);
            if (cnt < 2LL * e) {
                divisible = false;
                break;
            }
        }
        if (!divisible) {
            found = true;
            break;
        }
    }
    ensuref(found, "No valid key exists in the range [%lld, %lld]", A, B);

    inf.readEof();
    return 0;
}
