#include "testlib.h"

using namespace std;

long long best[11];

long long solve(int n) {
    if (best[n] != -1) return best[n];
    if (n <= 1) return best[n] = 0;
    long long res = 0;
    for (int b = 1; b < n; ++b) {
        int c = n - b;
        long long cur = 1LL * b * c + solve(b) + solve(c);
        if (cur > res) res = cur;
    }
    return best[n] = res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // N is a positive integer with canonical form, 1 <= N <= 10
    int N = inf.readInt(1, 10, "N");
    inf.readEoln();

    // Precompute and check the promised property: answer always exists and
    // is small; here we just compute it to verify no overflow or other issues.
    for (int i = 0; i <= 10; ++i) best[i] = -1;
    long long ans = solve(N);

    // Additional global sanity check: result should fit in 32-bit signed int.
    ensuref(ans >= 0 && ans <= (1LL << 31) - 1,
            "Computed maximal fun %lld for N=%d is out of expected range",
            ans, N);

    inf.readEof();
}
