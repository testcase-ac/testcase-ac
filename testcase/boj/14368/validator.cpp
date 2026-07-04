#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int jackets = inf.readInt(1, 10, "J");
        inf.readSpace();
        int pants = inf.readInt(jackets, 10, "P");
        inf.readSpace();
        int shirts = inf.readInt(pants, 10, "S");
        inf.readSpace();
        inf.readInt(1, 10, "K");
        inf.readEoln();
    }

    inf.readEof();
}
