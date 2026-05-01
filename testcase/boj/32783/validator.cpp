#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

// We only validate input format and constraints, not the combinatorial answer.

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 200;
    const long long MAX_A = 1000000000LL;
    const int MAX_M = 44640;
    const int MAX_C = 300000;
    const int RATE = 96; // 96원/kWh

    int n = inf.readInt(1, MAX_N, "n");
    inf.readEoln();

    vector<long long> a(n);
    vector<int> m(n);

    for (int i = 0; i < n; ++i) {
        a[i] = inf.readLong(1LL, MAX_A, "a_i");
        inf.readSpace();
        m[i] = inf.readInt(1, MAX_M, "m_i");
        inf.readEoln();

        // a is multiple of 250
        ensuref(a[i] % 250LL == 0,
                "a_%d must be multiple of 250, but got %lld", i + 1, a[i]);
        // m is multiple of 15
        ensuref(m[i] % 15 == 0,
                "m_%d must be multiple of 15, but got %d", i + 1, m[i]);
    }

    int c1 = inf.readInt(1, MAX_C, "c1");
    inf.readSpace();
    int c2 = inf.readInt(c1, MAX_C, "c2");
    inf.readEoln();

    // Optional global sanity: maximum possible cost (all computers used as given)
    // does not need to be checked against c2 because statement does not require
    // that some subset matches the billed range; it's just information for the solution.

    // However, we can at least check that the theoretical cost for each computer
    // is integral in won under the given rate and unit conventions.
    //
    // Interpretation: a W used for m minutes -> energy = a * m / 1000 (W*min to Wh)
    // 1 kWh = 1000 Wh, rate is 96원/kWh.
    // Cost in won = a * m * RATE / (60 * 1000 * 1000)? The exact unit conversion
    // is unspecified in the statement; since it's a solution detail and not
    // explicitly constrained in input, we do not enforce extra numeric properties.

    inf.readEof();
}
