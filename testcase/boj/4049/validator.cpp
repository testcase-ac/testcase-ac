#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCells = 0;
    int caseIndex = 1;
    while (true) {
        int r = inf.readInt(0, 500, "r");
        inf.readSpace();
        int c = inf.readInt(0, 500, "c");
        inf.readEoln();

        if (r == 0 && c == 0) {
            break;
        }

        setTestCase(caseIndex);
        ensuref(r > 0 && c > 0, "case %d has only one zero dimension: r=%d c=%d",
                caseIndex, r, c);

        totalCells += 1LL * r * c;
        // CHECK: the statement has sentinel-terminated cases with no count bound.
        ensuref(totalCells <= 250000LL, "total matrix cells exceed practical cap");

        for (int i = 0; i < r; ++i) {
            for (int j = 0; j < c; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(1, 65536, "a_ij");
            }
            inf.readEoln();
        }

        ++caseIndex;
    }

    inf.readEof();
}
