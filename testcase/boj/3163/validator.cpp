#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read N, L, k
        int N = inf.readInt(3, 100000, "N");
        inf.readSpace();
        int L = inf.readInt(10, 5000000, "L");
        inf.readSpace();
        int k = inf.readInt(1, N, "k");
        inf.readEoln();

        // For checking unique absolute IDs
        unordered_set<long long> seenAbsID;
        seenAbsID.reserve(N * 2);

        // Read each ant
        int prev_p = 0;
        for (int i = 0; i < N; i++) {
            int p = inf.readInt(1, L - 1, "p_i");
            inf.readSpace();
            long long a = inf.readLong(-1000000000LL, 1000000000LL, "a_i");
            inf.readEoln();

            // Positions must be strictly increasing
            ensuref(p > prev_p,
                    "At test %d, ant index %d: position p_i = %d is not greater than previous p = %d",
                    tc, i, p, prev_p);
            prev_p = p;

            // ID must be non-zero
            ensuref(a != 0,
                    "At test %d, ant index %d: ID a_i must be non-zero but found %lld",
                    tc, i, a);

            // Absolute ID uniqueness
            long long absa = llabs(a);
            // By range check of readLong, absa ∈ [0,1e9], but we ensure it's >=1
            ensuref(absa >= 1,
                    "At test %d, ant index %d: absolute ID must be at least 1 but got %lld",
                    tc, i, absa);
            ensuref(!seenAbsID.count(absa),
                    "At test %d, ant index %d: duplicate absolute ID %lld",
                    tc, i, absa);
            seenAbsID.insert(absa);
        }
    }

    inf.readEof();
    return 0;
}
