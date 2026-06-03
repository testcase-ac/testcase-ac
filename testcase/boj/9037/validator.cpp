#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not specify an upper bound for T; use the repo default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 10, "N");
        inf.readEoln();

        inf.readInts(n, 1, 30, "C_i");
        inf.readEoln();
    }

    inf.readEof();
}
