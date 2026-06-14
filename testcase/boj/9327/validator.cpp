#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        inf.readInt(0, 1000000000, "e");
        inf.readEoln();

        inf.readInts(n, 1, 2000, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
