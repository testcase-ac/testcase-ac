#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        inf.readInt(1, 100000, "R");
        inf.readSpace();
        int a = inf.readInt(1, 500, "A");
        inf.readSpace();
        int b = inf.readInt(2, 1000, "B");
        inf.readEoln();

        ensuref(2 * a <= b, "2*A must be <= B, got A=%d and B=%d", a, b);
    }

    inf.readEof();
}
