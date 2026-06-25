#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 50, "N");
        inf.readSpace();
        int m = inf.readInt(1, 50, "M");
        inf.readEoln();

        for (int row = 1; row <= n; ++row) {
            inf.readInts(m, 2, 10000, "a_i_j");
            inf.readEoln();
        }
    }

    inf.readEof();
}
