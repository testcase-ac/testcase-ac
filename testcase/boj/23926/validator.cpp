#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        long long l = inf.readLong(1LL, 1000000000000000000LL, "L");
        inf.readSpace();
        long long r = inf.readLong(1LL, 1000000000000000000LL, "R");
        inf.readEoln();

        ensuref(l <= r, "L must be at most R, got L=%lld and R=%lld", l, r);
    }

    inf.readEof();
}
