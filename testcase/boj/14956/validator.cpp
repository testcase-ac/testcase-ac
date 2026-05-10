#include "testlib.h"
#include <cmath>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single line: n m
    long long n = inf.readLong(1LL, (1LL << 15), "n"); // since k <= 15, n <= 2^15
    inf.readSpace();
    long long m = inf.readLong(1LL, (1LL << 30), "m"); // m <= 2^(2k) with k<=15 -> <= 2^30
    inf.readEoln();

    // Check that n is a power of two and determine k
    // n = 2^k, 0 < k <= 15
    ensuref((n & (n - 1)) == 0, "n must be a power of two, but got %lld", n);

    int k = 0;
    {
        long long tmp = n;
        while (tmp > 1) {
            tmp >>= 1;
            ++k;
        }
    }
    ensuref(1 <= k && k <= 15, "k must satisfy 0 < k <= 15, but derived k = %d from n = %lld", k, n);

    // Check that m <= 2^(2k)
    long long maxM = 1LL << (2 * k);
    ensuref(m <= maxM, "m must be <= 2^(2k) = %lld for k = %d, but got m = %lld", maxM, k, m);

    inf.readEof();
}
