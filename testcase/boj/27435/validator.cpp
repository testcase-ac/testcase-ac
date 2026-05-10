#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// For N up to 1e18, we only need to validate numeric range and format;
// there are no additional structural / global constraints to verify.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T: number of test cases
    long long T = inf.readLong(1LL, 100000LL, "T");
    inf.readEoln();

    for (long long tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        // N is an integer with 1 ≤ N ≤ 1e18
        long long N = inf.readLong(1LL, 1000000000000000000LL, "N");
        (void)N; // suppress unused warning

        inf.readEoln();
    }

    inf.readEof();
}
