#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeNCaseCount = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100000, "N");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "X");
        inf.readEoln();

        if (n > 100) {
            ++largeNCaseCount;
            ensuref(largeNCaseCount <= 10,
                    "at most 10 cases may have N > 100, found %d",
                    largeNCaseCount);
        }

        inf.readLongs(n, 1LL, 1000000000LL, "A_i");
        inf.readEoln();
    }

    inf.readEof();
}
