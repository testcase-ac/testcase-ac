#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000, "T");
    inf.readEoln();

    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100, "N");
        int counts[6];
        for (int i = 0; i < 6; ++i) {
            inf.readSpace();
            counts[i] = inf.readInt(0, n, "count");
        }
        inf.readEoln();

        ensuref(counts[0] + counts[1] + counts[2] == n,
                "case %d: A+B+C must equal N", caseIndex);
        ensuref(counts[3] + counts[4] + counts[5] == n,
                "case %d: D+E+F must equal N", caseIndex);

        for (int row = 0; row < 3; ++row) {
            inf.readInt(-100000, 100000, "P");
            for (int col = 1; col < 3; ++col) {
                inf.readSpace();
                inf.readInt(-100000, 100000, "P");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
