#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int a = inf.readInt(1, 10000000, "a");
        inf.readSpace();
        int b = inf.readInt(1, 10000000, "b");
        inf.readSpace();
        // CHECK: the statement only writes d <= max(a,b), but d is a desired
        // volume to be generated, so require a positive volume.
        int d = inf.readInt(1, 10000000, "d");
        inf.readEoln();

        ensuref(d <= a || d <= b, "d must be at most max(a, b): a=%d b=%d d=%d", a, b, d);
    }

    inf.readEof();
}
