#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of test cases, respecting statement bound (not the generic 1e5).
    int T = inf.readInt(1, 100, "T");
    inf.readEoln();

    vector<int> ns;
    ns.reserve(T);
    long long sum_n = 0;

    for (int tc = 0; tc < T; ++tc) {
        setTestCase(tc + 1);

        int n = inf.readInt(2, 100000, "n");
        sum_n += n;
        ensuref(sum_n <= 5000000LL,
                "Sum of n exceeds 5e6 after test case %d: current sum = %lld",
                tc + 1, sum_n);
        ns.push_back(n);

        inf.readEoln();
    }

    // No additional global structure assumptions that must be enforced on input
    // beyond numeric ranges and sum constraint.
    inf.readEof();
}
