#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(0, 100000000, "S");
        inf.readSpace();
        inf.readInt(0, 100000000, "N");
        inf.readSpace();
        inf.readInt(0, 100000000, "U");
        inf.readSpace();
        inf.readInt(0, 100000000, "P");
        inf.readSpace();
        inf.readInt(0, 100000000, "C");
        inf.readEoln();
    }

    inf.readEof();
}
