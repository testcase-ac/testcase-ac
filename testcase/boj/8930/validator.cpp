#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for T; use the local
    // default cap for unbounded testcase counts.
    int T = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= T; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int w = inf.readInt(1, n, "w");
        inf.readEoln();

        inf.readInts(n, 1, 10000, "u_i");
        inf.readEoln();
    }

    inf.readEof();
}
