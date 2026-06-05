#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 1000000000, "N");
        inf.readSpace();
        int s = inf.readInt(1, n, "S");
        inf.readSpace();
        int e = inf.readInt(1, n, "E");
        inf.readEoln();

        ensuref(s != e, "S and E must be different: %d", s);
    }

    inf.readEof();
}
