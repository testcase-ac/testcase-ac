#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readLong(1LL, 1000000000000000000LL, "N");
        inf.readSpace();
        inf.readInt(0, 10, "k");
        inf.readEoln();
    }

    inf.readEof();
}
