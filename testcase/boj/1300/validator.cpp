#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: 1 <= N <= 1e5
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Compute maximum allowed k = min(1e9, N^2)
    long long maxK = (long long)N * N;
    if (maxK > 1000000000LL) maxK = 1000000000LL;

    // Read k: 1 <= k <= maxK
    long long k = inf.readLong(1LL, maxK, "k");
    inf.readEoln();

    // No extra content
    inf.readEof();
    return 0;
}
