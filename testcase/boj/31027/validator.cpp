#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "n");
    inf.readEoln();

    for (int row = 1; row <= 2; ++row) {
        for (int col = 1; col <= n; ++col) {
            int expectedLow = (row == 1 && col == 1) || (row == 2 && col == n) ? 0 : 1;
            int expectedHigh = expectedLow == 0 ? 0 : 1000000;
            inf.readInt(expectedLow, expectedHigh, "a");

            if (col == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
