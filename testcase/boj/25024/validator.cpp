#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(0, 99, "x");
        inf.readSpace();
        inf.readInt(0, 99, "y");
        inf.readEoln();
    }

    inf.readEof();
}
