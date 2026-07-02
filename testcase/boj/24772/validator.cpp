#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseIndex = 1;
    while (true) {
        setTestCase(caseIndex);

        int r = inf.readInt(0, 1000, "r");
        inf.readSpace();
        int h = inf.readInt(0, 10000, "h");
        inf.readSpace();
        int s = inf.readInt(0, 100, "s");
        inf.readEoln();

        if (r == 0 && h == 0 && s == 0) {
            break;
        }

        ensuref(r >= 1, "case %d has non-sentinel r=%d", caseIndex, r);
        ensuref(h >= r, "case %d has h=%d smaller than r=%d", caseIndex, h, r);

        ++caseIndex;
    }

    inf.readEof();
}
