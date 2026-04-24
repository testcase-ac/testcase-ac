#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and k
    int n = inf.readInt(1, 250000, "n");
    inf.readSpace();
    // Compute total number of subarrays = n*(n+1)/2, fits in long long
    long long total = (long long)n * (n + 1) / 2;
    // Read k up to total (will further enforce k <= 10000)
    long long k = inf.readLong(1LL, total, "k");
    // Enforce k <= min(10000, total)
    long long maxk = min(10000LL, total);
    ensuref(k <= maxk,
            "k must be between 1 and min(10000, n*(n+1)/2) = %lld, but got %lld",
            maxk, k);
    inf.readEoln();

    // Read the fluctuation values
    for (int i = 0; i < n; i++) {
        long long ai = inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
