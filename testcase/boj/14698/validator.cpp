#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases T (1 ≤ T ≤ 100000)
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    // Track total sum of N across all test cases
    long long sumN = 0;
    // Constants for bounds
    const long long MIN_C = 2LL;
    const long long MAX_C = 2000000000000000000LL;  // 2 * 10^18
    const __int128 MAX_ENERGY = (__int128)MAX_C;

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        // Read N (1 ≤ N ≤ 60)
        int N = inf.readInt(1, 60, "N");
        inf.readEoln();

        // Read the N slime energies C_i (2 ≤ C_i ≤ 2×10^18)
        vector<long long> C = inf.readLongs(N, MIN_C, MAX_C, "C_i");
        inf.readEoln();

        // Update and check the total N constraint
        sumN += N;
        ensuref(sumN <= 1000000LL,
                "Sum of N across test cases exceeds limit: %lld", sumN);

        // Check that the product of all C_i does not exceed 2×10^18
        __int128 prod = 1;
        for (int i = 0; i < N; ++i) {
            prod *= C[i];
            ensuref(prod <= MAX_ENERGY,
                    "Product of energies in test case %d exceeds limit: currently %lld",
                    tc, (long long)prod);
        }
    }

    inf.readEof();
    return 0;
}
