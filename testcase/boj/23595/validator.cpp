#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);
        int y = inf.readInt(-1000000, 1000000, "Y");
        ensuref(y != 0, "Y must be non-zero");
        inf.readEoln();
    }

    inf.readEof();
}
