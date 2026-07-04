#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();

    int largeCaseCount = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 100000, "N");
        inf.readEoln();

        if (n > 10000) {
            ++largeCaseCount;
        }

        for (int i = 1; i <= n; ++i) {
            inf.readLong(-1000000000LL, 1000000000LL, "X_i");
            inf.readSpace();
            inf.readLong(-1000000000LL, 1000000000LL, "Y_i");
            inf.readEoln();
        }
    }

    ensuref(largeCaseCount <= 10,
            "at most 10 cases may have N greater than 10000, found %d",
            largeCaseCount);
    inf.readEof();
}
