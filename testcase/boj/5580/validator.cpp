#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 7, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int s = inf.readInt(1, 3000, "S");
    inf.readEoln();

    int cells = n * n;
    ensuref(m >= cells,
            "at least %d distinct numbers are needed, but M is %d",
            cells, m);

    int minSum = cells * (cells + 1) / 2;
    int maxSum = cells * (2 * m - cells + 1) / 2;
    ensuref(minSum <= s && s <= maxSum,
            "no valid board can have sum S=%d for N=%d and M=%d; allowed sum range is [%d, %d]",
            s, n, m, minSum, maxSum);

    inf.readEof();
}
