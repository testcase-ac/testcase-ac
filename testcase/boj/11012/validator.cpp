#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of test cases
    int T = inf.readInt(1, 20, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; tc++) {
        setTestCase(tc);

        // Read n and m
        int n = inf.readInt(1, 10000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 50000, "m");
        inf.readEoln();

        // Read folk coordinates
        for (int i = 0; i < n; i++) {
            int x = inf.readInt(0, 100000, "x_i");
            inf.readSpace();
            int y = inf.readInt(0, 100000, "y_i");
            inf.readEoln();
        }

        // Read parade queries
        for (int i = 0; i < m; i++) {
            int l = inf.readInt(0, 100000, "l_i");
            inf.readSpace();
            int r = inf.readInt(0, 100000, "r_i");
            ensuref(l <= r,
                    "Query %d in test case %d: l (%d) must be <= r (%d)",
                    i + 1, tc, l, r);
            inf.readSpace();
            int b = inf.readInt(0, 100000, "b_i");
            inf.readSpace();
            int t = inf.readInt(0, 100000, "t_i");
            ensuref(b <= t,
                    "Query %d in test case %d: b (%d) must be <= t (%d)",
                    i + 1, tc, b, t);
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
