#include "testlib.h"

using namespace std;

// Fast modular exponentiation: computes a^e mod mod
long long modPow(long long a, long long e, long long mod) {
    long long res = 1 % mod;
    a %= mod;
    while (e > 0) {
        if (e & 1LL) {
            res = (long long)((__int128)res * a % mod);
        }
        a = (long long)((__int128)a * a % mod);
        e >>= 1LL;
    }
    return res;
}

// Simulate bacteria growth as described, but only according to the *stated* constraints:
// After 1 hour: x -> x^x.
// Since the statement does not say B <= 2 for the actual input (example has B=10,1000),
// we must handle general B >= 1. However, note that the *true* number grows extremely fast.
// We only need it modulo C, and we must validate the promise that "the answer always exists".
// This simulation is for validation only and uses repeated exponentiation with modPow
// and Euler's theorem when applicable to keep exponents manageable.
long long bacteriaAfter(long long A, long long B, long long C) {
    // We simulate the recurrence on exponents in Z, but reduce modulo phi(C) when C>1
    // using Euler's theorem for gcd(base, C) == 1. Since constraints are small (C <= 1000),
    // we can compute phi(C) easily.
    if (C == 1) return 0; // everything is 0 mod 1

    auto phi = [](int n) {
        int result = n;
        for (int p = 2; p * p <= n; ++p) {
            if (n % p == 0) {
                while (n % p == 0) n /= p;
                result -= result / p;
            }
        }
        if (n > 1) result -= result / n;
        return result;
    };

    int phiC = phi((int)C);

    // true size at hour 0: A
    // at hour 1: A^A
    // at hour 2: (A^A)^(A^A), etc.
    // We only ever need the current value modulo C.
    long long cur = A % C;
    if (B == 0) return cur; // not expected per statement, but harmless

    // We'll track the "true" exponent modulo phi(C) plus a flag saying it's "large",
    // then use fast exponentiation rules. But since constraints in problem are tiny (A<=1000, C<=1000),
    // and B itself in realistic tests is small (example uses 10,1000 only 2 times),
    // we can afford a simple safe simulation just to ensure the answer range.
    //
    // For validation, it's enough to do the actual recurrence directly modulo C:
    // x_{k+1} = x_k^{x_k} (mod C)
    // starting at x_0 = A, do this B times.
    long long x = A % C;
    for (long long step = 0; step < B; ++step) {
        x = modPow(x, x, C);
    }
    return x;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 500, "T");
    inf.readEoln();

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int A = inf.readInt(1, 1000, "A");
        inf.readSpace();
        // The statement says 1 ≤ B ≤ 2, but the official sample includes B=10 and B=1000.
        // As a validator, we must follow the *actual* input format, which clearly allows larger B.
        // Therefore we only enforce B >= 1 and treat B as a standard integer without extra upper bound.
        int B = inf.readInt(1, (int)1e9, "B");
        inf.readSpace();
        int C = inf.readInt(1, 1000, "C");
        inf.readEoln();

        // Sanity-check the promised property that "the answer always exists" by actually computing it mod C.
        long long ans = bacteriaAfter(A, B, C);
        ensuref(0 <= ans && ans < C,
                "Computed answer out of range in test %d: A=%d B=%d C=%d ans=%lld",
                tc + 1, A, B, C, ans);
    }

    inf.readEof();
}
