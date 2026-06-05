#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 512, "N");
        inf.readEoln();

        int previousX = -1;
        for (int i = 1; i <= n; ++i) {
            int x = inf.readInt(0, 5000, "x");
            inf.readSpace();
            inf.readInt(0, 5000, "y");
            inf.readEoln();

            ensuref(previousX < x,
                    "x-coordinates must be strictly increasing, previous=%d current=%d at point %d",
                    previousX, x, i);
            previousX = x;
        }
    }

    inf.readEof();
}
