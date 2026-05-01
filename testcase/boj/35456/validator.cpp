#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N: number of inequalities
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // We must ensure A,B,C are within [-1e9,1e9] and A != 0
    // Also, based on the statement, the system is guaranteed to have either
    // finite or infinite integer solutions; nothing else is promised,
    // so we don't enforce any extra "answer exists" property beyond the ranges.

    // We will also check the global property that if the system admits integer
    // solutions, the count doesn't exceed 2*10^18, to avoid overflow issues
    // in intended solutions (this is not stated, so we DON'T enforce it).

    // Just read and range-check all inequalities.
    for (int i = 0; i < N; ++i) {
        long long A = inf.readLong(-1000000000LL, 1000000000LL, "A_i");
        inf.readSpace();
        long long B = inf.readLong(-1000000000LL, 1000000000LL, "B_i");
        inf.readSpace();
        long long C = inf.readLong(-1000000000LL, 1000000000LL, "C_i");
        inf.readEoln();

        ensuref(A != 0, "A_i must be non-zero at line %d", i + 2);
        // No further semantic checks: solution is supposed to process inequalities
        // and compute the number of integer x such that A*x + B <= C for all i.
    }

    inf.readEof();
}
