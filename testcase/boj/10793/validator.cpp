#include "testlib.h"
#include <bits/stdc++.h>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int TMAX = 500;
    const long long AMIN = 1LL;
    const long long AMAX = 500000LL;

    int n = inf.readInt(1, TMAX, "n");
    inf.readEoln();

    for (int tc = 0; tc < n; ++tc) {
        setTestCase(tc + 1);

        long long a_lo = inf.readLong(AMIN, AMAX, "a_lo");
        inf.readSpace();
        long long a_hi = inf.readLong(AMIN, AMAX, "a_hi");
        inf.readEoln();

        ensuref(a_lo <= a_hi,
                "For test case %d, a_lo (%lld) must be <= a_hi (%lld)",
                tc + 1, a_lo, a_hi);
    }

    inf.readEof();
}
