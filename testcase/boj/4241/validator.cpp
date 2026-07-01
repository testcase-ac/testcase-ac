#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    int totalLength = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "n");
        inf.readSpace();
        int m = inf.readInt(0, 1000, "m");
        inf.readSpace();
        int d = inf.readInt(0, 10, "d");
        inf.readEoln();

        if (n == 0 && m == 0 && d == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);

        ensuref(1 <= n && n < m, "expected 1 <= n < m, got n=%d m=%d", n, m);
        ensuref(2 <= d && d <= 10, "expected 2 <= d <= 10, got d=%d", d);

        totalLength += m - n + 1;
        // CHECK: the statement has no test case count; cap aggregate sequence size to one hundred largest cases.
        ensuref(totalLength <= 100000, "aggregate sequence length is too large: %d", totalLength);
    }

    inf.readEof();
}
