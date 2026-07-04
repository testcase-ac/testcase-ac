#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int c = inf.readInt(1, 10, "C");
        inf.readSpace();
        inf.readInt(1, c, "N");
        inf.readEoln();
    }

    inf.readEof();
}
