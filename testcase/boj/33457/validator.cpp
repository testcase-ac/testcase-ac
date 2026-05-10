#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static const long long MOD = 998244353LL;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    long long sum_nm_sq = 0;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        long long n = inf.readLong(0LL, 300LL, "n");
        inf.readSpace();
        long long m = inf.readLong(0LL, 300LL, "m");
        inf.readSpace();
        long long k = inf.readLong(0LL, (long long)1e9, "k"); // upper bound from problem: only via k^2 + l^2 <= 2023
        inf.readSpace();
        long long l = inf.readLong(0LL, (long long)1e9, "l");
        inf.readEoln();

        // Check k^2 + l^2 <= 2023, avoiding overflow by using long long
        long long k2 = k * k;
        long long l2 = l * l;
        ensuref(k2 + l2 <= 2023,
                "For test %d: constraint k^2 + l^2 <= 2023 violated (k=%lld, l=%lld, k^2+l^2=%lld)",
                tc + 1, k, l, k2 + l2);

        // Global constraint on sum of n^2 + m^2
        long long add = n * n + m * m;
        sum_nm_sq += add;
        ensuref(sum_nm_sq <= 200000LL,
                "Sum over test cases of (n^2 + m^2) exceeds 2e5 after test %d (current sum=%lld)",
                tc + 1, sum_nm_sq);

        // Optional heavy global property checks:
        // The problem does not guarantee existence/size of answer beyond modular arithmetic,
        // and no additional global structure is implied; thus no extra simulation is needed.
        // However, we can sanity-check that (ab + cd + 1) never overflows 64-bit:
        long long max_ab = n * n;
        long long max_cd = m * m;
        long long max_val = max_ab + max_cd + 1;
        ensuref(max_val >= 1 && max_val <= (long long)1e11,
                "Internal sanity check failed: (ab+cd+1) out of expected safe range at test %d (n=%lld,m=%lld)",
                tc + 1, n, m);

        // Additionally, we may check that exponent e^f (xor) is within reasonable bound (it always is,
        // limited by max(k,l)), but k,l already bounded via k^2+l^2<=2023.
        long long max_xor = max(k, l);
        ensuref(max_xor <= 2023,
                "Internal sanity check failed: max(k,l) should be <= 2023 by problem constraint, but got %lld at test %d",
                max_xor, tc + 1);
    }

    inf.readEof();
}
