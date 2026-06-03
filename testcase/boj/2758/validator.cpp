#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T, so use the local
    // practical cap for testcase counts. The English statement allows T = 0.
    int t = inf.readInt(0, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 10, "n");
        inf.readSpace();
        int m = inf.readInt(1, 2000, "m");
        inf.readEoln();

        ensuref(n <= m, "n must be at most m, got n=%d and m=%d", n, m);
    }

    inf.readEof();
}
