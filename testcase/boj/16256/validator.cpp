#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not bound t directly; since every test case has
    // at least one cell and total cells are bounded by 100000, t is capped here.
    int t = inf.readInt(1, 100000, "t");
    inf.readEoln();

    int totalCells = 0;
    for (int caseIndex = 1; caseIndex <= t; ++caseIndex) {
        setTestCase(caseIndex);

        int n = inf.readInt(1, 100, "n");
        inf.readSpace();
        int m = inf.readInt(1, 100, "m");
        inf.readSpace();
        int k = inf.readInt(1, std::max(n, m), "k");
        inf.readEoln();

        totalCells += n * m;
        ensuref(totalCells <= 100000,
                "total number of cells exceeds 100000 after case %d: %d",
                caseIndex, totalCells);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j > 0) {
                    inf.readSpace();
                }
                inf.readInt(0, 1, "a_ij");
            }
            inf.readEoln();
        }
    }

    inf.readEof();
}
