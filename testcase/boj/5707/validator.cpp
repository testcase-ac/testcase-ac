#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long totalCells = 0;
    int testCase = 1;

    while (true) {
        int n = inf.readInt(0, 100, "N");
        inf.readSpace();
        int r = inf.readInt(0, 100, "R");
        inf.readSpace();
        int c = inf.readInt(0, 100, "C");
        inf.readSpace();
        int k = inf.readInt(0, 100, "K");
        inf.readEoln();

        if (n == 0 && r == 0 && c == 0 && k == 0) {
            break;
        }

        setTestCase(testCase++);
        ensuref(2 <= n, "N must be at least 2, got %d", n);
        ensuref(2 <= r, "R must be at least 2, got %d", r);
        ensuref(2 <= c, "C must be at least 2, got %d", c);
        ensuref(1 <= k, "K must be at least 1, got %d", k);

        totalCells += 1LL * r * c;
        // CHECK: The statement does not bound the number of test cases.
        ensuref(totalCells <= 5000000LL, "too many grid cells across test cases");

        for (int row = 0; row < r; ++row) {
            for (int col = 0; col < c; ++col) {
                inf.readInt(0, n - 1, "H_rc");
                if (col + 1 < c) {
                    inf.readSpace();
                } else {
                    inf.readEoln();
                }
            }
        }
    }

    inf.readEof();
}
