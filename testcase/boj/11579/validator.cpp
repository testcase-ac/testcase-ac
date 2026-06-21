#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement omits an upper bound for T; keep total scalar input
    // under the local practical cap while accepting ordinary multi-case files.
    const long long maxScalarTokens = 5000000LL;
    long long scalarTokens = 1;

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 500, "n");
        inf.readEoln();
        scalarTokens += 1LL + 1LL * n * n + n;
        ensuref(scalarTokens <= maxScalarTokens,
                "too many scalar tokens through test case %d", tc);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int x = inf.readInt(-1000, 1000, "x_ij");
                if (j + 1 < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }

                if (j < i) {
                    ensuref(x == 0,
                            "row %d has nonzero value before first 1 at column %d",
                            i + 1, j + 1);
                } else if (j == i) {
                    ensuref(x == 1,
                            "row %d must have first 1 at column %d", i + 1, j + 1);
                }
            }
        }

        for (int i = 0; i < n; ++i) {
            inf.readInt(-500000000, 500000000, "y_i");
            if (i + 1 < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
