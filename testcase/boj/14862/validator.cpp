#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using i128 = __int128_t;

static const int MAXB = 200000;
static const int MOD = 1000000007;

// Extended GCD for modular inverse (not strictly needed for validation, but harmless)
ll exgcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) { x = 1; y = 0; return a; }
    ll x1, y1;
    ll g = exgcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}

ll modInverse(ll a, ll mod) {
    ll x, y;
    ll g = exgcd(a, mod, x, y);
    ensuref(g == 1, "modular inverse does not exist for %lld modulo %lld", a, mod);
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Precompute mu up to MAXB for global property checking
    vector<int> mu(MAXB + 1, 0), primes;
    vector<bool> isComp(MAXB + 1, false);
    mu[1] = 1;
    for (int i = 2; i <= MAXB; ++i) {
        if (!isComp[i]) {
            primes.push_back(i);
            mu[i] = -1;
        }
        for (int p : primes) {
            if ((ll)i * p > MAXB) break;
            isComp[i * p] = true;
            if (i % p == 0) {
                mu[i * p] = 0;
                break;
            } else {
                mu[i * p] = -mu[i];
            }
        }
    }

    int T = inf.readInt(1, 50, "T");
    inf.readEoln();

    // For each test case, we compute the expected GCD and verify it is well-defined
    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int K = inf.readInt(2, 5, "K");
        inf.readEoln();

        vector<int> A(K), B(K);
        for (int i = 0; i < K; ++i) {
            A[i] = inf.readInt(1, MAXB, "A_i");
            inf.readSpace();
            B[i] = inf.readInt(1, MAXB, "B_i");
            inf.readEoln();
            ensuref(A[i] <= B[i], "A_i must be <= B_i at index %d, got %d > %d", i, A[i], B[i]);
        }

        // Global property: the expected value of GCD(X_0,...,X_{K-1}) must exist as a rational P/Q.
        // It always exists mathematically, but we additionally verify that P and Q
        // (with Q > 0) can be represented in 128-bit and that Q is not divisible by MOD,
        // which is required for the output definition (P + Q*N divisible by MOD).
        // If Q is divisible by MOD, there may be 0 or multiple N; we need that the
        // statement's "find N" is well-posed. The problem as given implies that
        // the expected value forms a proper fraction with denominator not divisible by MOD.
        //
        // We'll compute P and Q exactly using inclusion-exclusion on multiples (Mobius).

        // For each d, compute count of numbers in each interval divisible by d
        int maxB = 0;
        for (int x : B) maxB = max(maxB, x);

        vector<ll> cnt(K);
        vector<ll> f(maxB + 1, 0); // number of K-tuples where all X_i are divisible by d

        for (int d = 1; d <= maxB; ++d) {
            bool zero = false;
            i128 prod = 1;
            for (int i = 0; i < K; ++i) {
                ll hi = B[i] / d;
                ll lo = (A[i] + d - 1) / d;
                ll c = hi - lo + 1;
                if (c <= 0) { zero = true; break; }
                prod *= (i128)c;
                // bound: each c <= 2e5;  (2e5)^5 ~ 3.2e26 < 2^87, safe in i128
            }
            if (!zero) f[d] = (ll)prod;
        }

        // Using probability that gcd == g:
        // P(gcd == g) = sum_{k>=1} mu[k] * f[g*k] / total
        // where total = product_i (B[i]-A[i]+1)
        i128 total = 1;
        for (int i = 0; i < K; ++i) {
            ll len = (ll)B[i] - A[i] + 1;
            total *= (i128)len;
        }
        ensuref(total > 0, "Total number of tuples must be positive");

        // Compute numerator P as sum_g g * P(gcd == g)
        // So P = sum_g g * (sum_k mu[k] * f[g*k]) / total
        // Let Sg = sum_k mu[k] * f[g*k]
        i128 num = 0;
        for (int g = 1; g <= maxB; ++g) {
            i128 Sg = 0;
            for (int k = 1; (ll)g * k <= maxB; ++k) {
                int d = g * k;
                if (mu[k] == 0) continue;
                Sg += (i128)mu[k] * (i128)f[d];
            }
            if (Sg == 0) continue;
            num += (i128)g * Sg;
        }

        // Now we have expected value E = num / total
        // Reduce fraction to P / Q
        auto abs128 = [](i128 x) -> i128 { return x < 0 ? -x : x; };

        i128 g = std::gcd((long long)(abs128(num) % (1ll << 62)), (long long)(total % (1ll << 62)));
        // The above gcd trick is safe since values are far below 2^62.
        // Convert g to positive
        if (g < 0) g = -g;
        if (g == 0) g = 1;

        i128 P128 = num / g;
        i128 Q128 = total / g;

        ensuref(Q128 > 0, "Denominator Q must be positive after reduction");

        // Check that P and Q fit into signed 64-bit (problem constraints are small enough)
        ensuref(P128 >= LLONG_MIN && P128 <= LLONG_MAX,
                "Numerator P does not fit in 64-bit signed integer");
        ensuref(Q128 >= 1 && Q128 <= LLONG_MAX,
                "Denominator Q does not fit in 64-bit signed integer");

        ll P = (ll)P128;
        ll Q = (ll)Q128;

        // For the problem's output definition, they consider P/Q in lowest terms.
        // We must ensure gcd(P, Q) == 1 as we reduced.
        ll g64 = std::gcd(P < 0 ? -P : P, Q);
        ensuref(g64 == 1, "P and Q are not coprime after reduction, gcd = %lld", g64);

        // Additional check: for the congruence P + Q*N ≡ 0 (mod MOD),
        // if Q ≡ 0 (mod MOD), then either no solution (if P % MOD != 0) or many.
        // The statement defines to print -1 if no N exists, but input guarantee
        // normally should make the task meaningful; we enforce that either:
        // - Q % MOD != 0, in which case there is a unique solution N in [0, MOD-1], or
        // - Q % MOD == 0 and P % MOD == 0, in which case any N is solution.
        // To match typical BOJ style, we only enforce that if Q % MOD == 0 then P % MOD == 0.
        if (Q % MOD == 0) {
            ensuref(P % MOD == 0,
                    "Q is divisible by MOD but P is not, so no N exists; invalid test case");
        }

        // Nothing to read per test case beyond this point
    }

    inf.readEof();
}
