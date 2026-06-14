#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        long long x = inf.readLong(0LL, 1000000000LL, "x");
        inf.readSpace();
        long long y = inf.readLong(0LL, 1000000000LL, "y");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "a");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "b");
        inf.readEoln();

        ensuref(x < y, "expected x < y, got x=%lld and y=%lld", x, y);
    }

    inf.readEof();
}
