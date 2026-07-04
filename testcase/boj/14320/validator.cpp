#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(1, 100, "N");
        inf.readSpace();
        inf.readInt(1, 1000000000, "M");
        inf.readEoln();
    }

    inf.readEof();
}
