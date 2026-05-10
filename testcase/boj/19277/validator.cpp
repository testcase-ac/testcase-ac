#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int NMIN = 1;
    const int NMAX = 200000;
    const int QMIN = 1;
    const int QMAX = 200000;
    const int AMIN = 0;
    const int AMAX = 100000000;
    const int XDIVADD_MIN = 1;
    const int XDIVADD_MAX = 1000;

    int N = inf.readInt(NMIN, NMAX, "N");
    inf.readSpace();
    int Q = inf.readInt(QMIN, QMAX, "Q");
    inf.readEoln();

    vector<long long> a(N);
    for (int i = 0; i < N; ++i) {
        a[i] = inf.readInt(AMIN, AMAX, "a_i");
        if (i + 1 < N) inf.readSpace();
    }
    inf.readEoln();

    // Simulate queries to ensure that all operations are well-defined as per statement.
    // Values can grow, but long long is enough: max growth per operation is +1000,
    // Q <= 2e5, so max increase per element <= 2e8, starting from 1e8 -> well within 64-bit.
    for (int qi = 0; qi < Q; ++qi) {
        int t = inf.readInt(0, 2, "t_i");
        inf.readSpace();
        int l = inf.readInt(0, N - 1, "l_i");
        inf.readSpace();
        int r = inf.readInt(0, N - 1, "r_i");
        inf.readSpace();
        long long x = inf.readInt(0, 1000, "x_i"); // will further constrain below
        inf.readEoln();

        ensuref(l <= r, "Query %d has l > r: l=%d r=%d", qi + 1, l, r);

        if (t == 0) { // ADD
            ensuref(1 <= x && x <= XDIVADD_MAX,
                    "Query %d (ADD) must have 1 <= x <= %d, got %lld",
                    qi + 1, XDIVADD_MAX, x);
            for (int i = l; i <= r; ++i) {
                a[i] += x;
            }
        } else if (t == 1) { // DIV
            ensuref(1 <= x && x <= XDIVADD_MAX,
                    "Query %d (DIV) must have 1 <= x <= %d, got %lld",
                    qi + 1, XDIVADD_MAX, x);
            for (int i = l; i <= r; ++i) {
                // floor(a[i] / x) with a[i] integer and x>0 is standard integer division
                if (a[i] >= 0)
                    a[i] = a[i] / x;
                else
                    a[i] = (a[i] - (x - 1)) / x; // safer for negatives, though not needed here
            }
        } else { // t == 2, MAX query
            ensuref(x == 0, "Query %d (MAX) must have x = 0, got %lld", qi + 1, x);
            // Ensure the max is well-defined and within 64-bit range.
            long long curMax = a[l];
            for (int i = l + 1; i <= r; ++i) {
                if (a[i] > curMax) curMax = a[i];
            }
            // No need to store; just ensuring the range is non-empty and max is computable.
        }
    }

    inf.readEof();
}
