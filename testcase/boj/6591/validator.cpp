#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long N_MAX = 2147483647LL; // 2^31-1
    const __int128 LIMIT = (__int128)1 << 31; // 2^31

    int real_tests = 0;
    for (int tc = 1;; tc++) {
        // Read n and k
        long long n = inf.readLong(0LL, N_MAX, "n");
        inf.readSpace();
        long long k = inf.readLong(0LL, N_MAX, "k");
        inf.readEoln();

        // Check for sentinel
        if (n == 0 && k == 0) {
            break;
        }

        // Now this is a real test case
        real_tests++;
        ensuref(real_tests <= 100000,
                "Number of test cases exceeds the limit: %d > 100000",
                real_tests);

        // Validate basic constraints
        ensuref(n >= 1,
                "Test %d: n must be at least 1, but found %lld",
                tc, n);
        ensuref(k >= 0 && k <= n,
                "Test %d: k must satisfy 0 <= k <= n, but found k=%lld, n=%lld",
                tc, k, n);

        // Compute C(n, k) safely and check it is < 2^31
        long long kk = k;
        if (kk > n - kk) kk = n - kk;
        __int128 binom = 1;
        for (long long j = 1; j <= kk; ++j) {
            // Multiply then divide; the result is always integral for binomials
            binom = binom * (n - j + 1) / j;
        }
        // Check we didn't overflow beyond 64-bit
        long long binom_ll = (long long)binom;
        ensuref((__int128)binom_ll == binom,
                "Test %d: C(%lld, %lld) overflowed 64-bit",
                tc, n, k);
        // Check the problem guarantee: result < 2^31
        ensuref(binom < LIMIT,
                "Test %d: C(%lld, %lld) = %lld is not less than 2^31",
                tc, n, k, binom_ll);
    }

    inf.readEof();
    return 0;
}
