#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        // CHECK: M is bounded in the test-set constraints, not the global limit block.
        int m = inf.readInt(2, 1000, "M");
        inf.readSpace();
        int n = inf.readInt(1, 31, "N");
        inf.readSpace();
        inf.readInt(1, m, "P");
        inf.readEoln();

        for (int i = 1; i <= m; ++i) {
            inf.readInts(n, 1, 60000, "S_i_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
