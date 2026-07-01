#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int z = inf.readInt(1, 200, "z");
    inf.readEoln();

    long long totalSums = 0;
    for (int caseIndex = 1; caseIndex <= z; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 20, "n");
        inf.readEoln();

        int sumCount = (1 << n) - 1;
        totalSums += sumCount;
        ensuref(totalSums <= 10000000LL,
                "total number of sums exceeds 10000000 after case %d", caseIndex);

        for (int i = 0; i < sumCount; ++i) {
            inf.readInt(1, 2000000000, "sum");
            if (i + 1 == sumCount) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
