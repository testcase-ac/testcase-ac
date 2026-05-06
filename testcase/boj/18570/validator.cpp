#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// Modular arithmetic for 998244353
const int MOD = 998244353;

long long modPow(long long a, long long e) {
    long long r = 1 % MOD;
    a %= MOD;
    while (e > 0) {
        if (e & 1) r = (__int128)r * a % MOD;
        a = (__int128)a * a % MOD;
        e >>= 1;
    }
    return r;
}

// Compute expected min of n independent uniform[0, d_i] variables
// as a rational P/Q, and check that Q is not divisible by MOD.
// We do this in modular arithmetic: compute E mod MOD directly and
// verify well-definedness via construction, not by accessing P,Q.
long long computeExpectedMod(const vector<int>& d) {
    int n = (int)d.size();
    // We need to compute E[T] = ∫_0^∞ P(T > t) dt.
    // For U_i ~ Uniform(0, d_i), independent:
    // P(T > t) = Π_i max(0, (d_i - t)/d_i) = Π_i (1 - t/d_i) for t <= min d_i, else 0.
    // But for differing d_i, support shrinks as t passes each d_i.
    //
    // Alternative: derive formula in terms of sorted d_i.
    // Let d sorted ascending: a[0] <= a[1] <= ... <= a[n-1].
    // For t in [0, a[0]]: all active, contribution integral_0^{a0} Π_i (1 - t/a[i]) dt.
    // For t in [a[k-1], a[k]]: first k-1 routes expired (prob 0 for them), remaining n-k+1 active:
    //   Π_{i>=k} (1 - t/a[i]) where t in [a[k-1], a[k]].
    // However, once t > a[i], factor is 0, so T cannot exceed a[0]. In fact, min support is [0, a[0]].
    // So only first segment matters: 0..a[0] with all routes active.
    //
    // Thus T <= min_i d_i almost surely; P(T>t)=0 for t>=min d_i.
    // So E[T] = ∫_0^{m} Π_i (1 - t/d_i) dt, where m = min d_i.
    //
    // That integral yields a rational with denominator product of d_i * something small.
    // Instead of closed form in rationals, we can compute it symbolically as polynomial:
    // Π_i (1 - t/d_i) = Σ_{k=0}^n c_k t^k, with c_0=1, others from symmetric sums of 1/d_i.
    // Then E = Σ_k c_k * m^{k+1}/(k+1).
    //
    // All operations can be done modulo MOD since denominators (d_i and k+1) must be invertible
    // mod MOD for the promised tests, and if something isn't invertible we will detect by explicit check.

    vector<int> a = d;
    sort(a.begin(), a.end());
    long long m = a[0];

    // Build polynomial coefficients c_k in modulo field with indeterminate t,
    // where factor for route i is (1 - t / d_i).
    // Represent polynomial up to degree n (n <= 1e5; O(n^2) is impossible).
    // So the straightforward polynomial expansion is too big.
    //
    // Need a different derivation.
    //
    // Derivative trick:
    // Let F(t) = Π_i (1 - t/d_i). Then ln F(t) = Σ_i ln(1 - t/d_i).
    // But integrating F directly is hard numerically without expansions.
    //
    // Another approach: consider distribution of minimum of uniforms via order statistics with different ranges - nontrivial.
    //
    // However, this validator is allowed to be slower than solution but still must handle n up to 1e5.
    // O(n^2) is too slow, but O(n log MOD) or O(n log n) is fine.
    //
    // Let's seek a direct rational formula:
    // For independent Uniform(0, d_i), density f_i(x)=1/d_i on [0,d_i].
    // CDF of min: P(T > t) = Π_i P(U_i > t) = Π_i ((d_i - t)/d_i) for t <= m.
    // E[T] = ∫_0^m Π_i (d_i - t)/d_i dt.
    // Let D = Π_i d_i. Then E[T] = (1/D) ∫_0^m Π_i (d_i - t) dt.
    //
    // Polynomial Π_i (d_i - t) has roots at each d_i. Its antiderivative can be expressed via Lagrange basis:
    // Define G(t) = Π_i (t - d_i). Then Π_i (d_i - t) = (-1)^n G(t).
    // G(t) is monic degree n with known values at t = d_j: G(d_j)=0.
    // But we need integral from 0 to m of G(t), scaled.
    //
    // General degree-n polynomial integration still expensive for large n if we do full expansion.
    //
    // At this point, a fully correct symbolic validation seems too heavy.
    // But the problem's global guarantee is only:
    //   "answer can be represented as irreducible P/Q with Q not divisible by MOD"
    // This is automatically satisfied if for all i, d_i not divisible by MOD, because:
    // - The only denominators come from products of d_i and small integers (<= n+1).
    //   If any denominator has a factor MOD, then either some d_i or some integer (k+1) has factor MOD.
    // - But MOD is prime > n (since MOD = 998244353 > 1e5), so k+1 cannot introduce factor MOD.
    // Therefore, the only way Q is divisible by MOD is if some d_i is divisible by MOD.
    //
    // Hence, to enforce the statement's guarantee, it's enough to check that for all i, d_i % MOD != 0.
    // That is easy and O(n).
    //
    // We don't actually need to compute the expectation value, just to ensure Q not divisible by MOD.

    // This function only checks denominators invertible; we don't need to return a meaningful value.
    // We'll just return 0.
    for (int x : a) {
        // Denominators contain products of d_i, so if any d_i == 0 mod MOD, Q will be 0 mod MOD.
        ensuref(x % MOD != 0, "Interval d_i = %d is divisible by MOD=%d, which would make Q ≡ 0 (mod MOD)", x, MOD);
    }
    return 0;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    vector<int> d = inf.readInts(n, 1, 987654321, "d_i");
    inf.readEoln();

    // Global property: according to statement, final denominator Q of the rational
    // expectation must not be 0 modulo 998244353. As reasoned above, this is
    // violated exactly when some d_i is divisible by MOD (since other denominator
    // factors are integers <= n+1 < MOD).
    computeExpectedMod(d);

    inf.readEof();
}
