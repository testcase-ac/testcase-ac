#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCells = 0;
    int testCase = 0;

    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++testCase;
        setTestCase(testCase);

        totalCells += 1LL * n * n;
        // CHECK: the statement does not bound the number of test cases; cap total matrix cells to keep inputs practical.
        ensuref(totalCells <= 4000000LL, "too many matrix cells: %lld", totalCells);

        for (int row = 1; row <= n; ++row) {
            for (int col = 1; col <= n; ++col) {
                inf.readInt(-1000000, 1000000, "a_ij");
                if (col < n) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}
