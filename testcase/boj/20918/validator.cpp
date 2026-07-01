#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 1000, "n");
        inf.readSpace();
        int a = inf.readInt(0, 1000, "a");
        inf.readSpace();
        int b = inf.readInt(0, 1000, "b");
        inf.readEoln();

        ensuref(a <= b, "a must not exceed b: a=%d, b=%d", a, b);
    }

    inf.readEof();
}
