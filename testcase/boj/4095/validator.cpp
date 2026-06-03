#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxTotalCells = 4000000;
    int totalCells = 0;
    int caseCount = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 1000, "m");
        inf.readEoln();

        if (n == 0 && m == 0) {
            break;
        }

        ensuref(n >= 1 && m >= 1, "non-terminating dimensions must both be positive: n=%d, m=%d", n, m);

        ++caseCount;
        setTestCase(caseCount);

        // CHECK: The statement gives no test-case count; cap total cells to keep scalar input size practical.
        ensuref(totalCells <= maxTotalCells - n * m,
                "total matrix cells exceed practical cap %d",
                maxTotalCells);
        totalCells += n * m;

        for (int row = 1; row <= n; ++row) {
            for (int col = 1; col <= m; ++col) {
                inf.readInt(0, 1, "cell");
                if (col < m) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    // CHECK: The statement describes several test cases before the terminating 0 0 line.
    ensuref(caseCount >= 1, "at least one test case is required");

    inf.readEof();
}
