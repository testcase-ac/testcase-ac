#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases K (K ≥ 1, assume upper bound 100000)
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int tc = 1; tc <= K; ++tc) {
        setTestCase(tc);

        // n friends, c cars, l regions
        // Constraints: n ≤ 500 , c ≤ n , l ≤ c
        int n = inf.readInt(0, 500, "n");
        inf.readSpace();
        int c = inf.readInt(0, n, "c");
        inf.readSpace();
        int l = inf.readInt(0, c, "l");
        inf.readEoln();

        // Additional implied constraints:
        // If there are friends, regions must exist (their region is in [1, l]).
        if (n > 0) {
            ensuref(l >= 1, "When n > 0, l must be at least 1 (tc=%d, n=%d, l=%d)", tc, n, l);
        }
        // If there are cars, regions must exist (dest in [1, l]).
        if (c > 0) {
            ensuref(l >= 1, "When c > 0, l must be at least 1 (tc=%d, c=%d, l=%d)", tc, c, l);
        }

        // Read n friends:
        // Each line: region number in [1, l] and status I/S.
        for (int i = 0; i < n; ++i) {
            // When n > 0 we ensured l >= 1, so this is safe. If somehow l==0 here,
            // the range [1,0] would be invalid, but our ensures prevent that.
            int r = inf.readInt(1, l, "friend_region");
            inf.readSpace();
            // Exactly one character, either 'I' or 'S'
            string s = inf.readToken("[IS]", "status");
            inf.readEoln();
        }

        // Read c cars:
        // Each line: region number in [1, l] and capacity in [2, 8].
        for (int i = 0; i < c; ++i) {
            int r = inf.readInt(1, l, "car_region");
            inf.readSpace();
            int cap = inf.readInt(2, 8, "capacity");
            inf.readEoln();
        }
    }

    inf.readEof();
}
