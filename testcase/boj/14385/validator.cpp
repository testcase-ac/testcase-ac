#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(16, 16, "N");
        inf.readSpace();
        int j = inf.readInt(50, 50, "J");
        inf.readEoln();
    }

    inf.readEof();
}
