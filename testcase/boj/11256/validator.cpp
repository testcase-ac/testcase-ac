#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 10, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int j = inf.readInt(1, 1000, "J");
        inf.readSpace();
        int n = inf.readInt(1, 1000, "N");
        inf.readEoln();

        long long totalCapacity = 0;
        for (int i = 1; i <= n; ++i) {
            int r = inf.readInt(1, 10000, "R_i");
            inf.readSpace();
            int c = inf.readInt(1, 10000, "C_i");
            inf.readEoln();

            totalCapacity += 1LL * r * c;
        }

        ensuref(totalCapacity >= j,
                "test case %d has insufficient box capacity: total=%lld, J=%d",
                caseIndex, totalCapacity, j);
    }

    inf.readEof();
}
