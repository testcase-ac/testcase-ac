#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(1, 10000000, "N");
        inf.readSpace();
        inf.readInt(1, 10000000, "K");
        inf.readEoln();
    }

    inf.readEof();
}
