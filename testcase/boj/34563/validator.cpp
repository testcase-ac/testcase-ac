#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10000, "T");
    inf.readEoln();

    long long productSum = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(2, 500000, "N");
        inf.readSpace();
        int m = inf.readInt(2, 500000, "M");
        inf.readEoln();

        productSum += 1LL * n * m;
        ensuref(productSum <= 1000000LL,
                "sum of N*M exceeds 1000000 after case %d: %lld",
                caseIndex, productSum);
    }

    inf.readEof();
}
