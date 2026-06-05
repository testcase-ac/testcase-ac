#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(1, 1000000000, "n");
        inf.readEoln();
    }

    inf.readEof();
}
