#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    long long totalN = 0;
    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 200000, "n");
        inf.readEoln();

        totalN += n;
        // CHECK: The statement bounds n per test case but does not state an aggregate limit.
        ensuref(totalN <= 2000000LL, "sum of n exceeds practical validation cap");

        for (int i = 0; i < n; ++i) {
            if (i > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 999999999, "a_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
