#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 50000, "t");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        long long l = inf.readLong(1LL, 1000000000000000000LL, "l");
        inf.readSpace();
        long long r = inf.readLong(l, 1000000000000000000LL, "r");
        inf.readEoln();
    }

    inf.readEof();
}
