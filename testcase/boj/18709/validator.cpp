#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    int totalCells = 0;
    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        int n = inf.readInt(1, 300, "N");
        inf.readSpace();
        inf.readInt(0, 300, "K");
        inf.readEoln();

        totalCells += n * n;
        // CHECK: T has no statement upper bound; cap aggregate matrix cells to one largest case.
        ensuref(totalCells <= 300 * 300,
                "sum of N^2 over test cases must not exceed 90000");

        for (int i = 0; i < n; ++i) {
            inf.readInts(n, 0, 1, "F_ij");
            inf.readEoln();
        }
    }

    inf.readEof();
}
