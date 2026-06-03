#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 14, "n");
        if (n == 0) {
            inf.readEoln();
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        ensuref(n >= 2, "n must be either 0 terminator or in [2, 14], got %d", n);

        int nonzero = 0;
        for (int i = 0; i < n; ++i) {
            inf.readSpace();
            int digit = inf.readInt(0, 9, "digit");
            if (digit != 0) {
                ++nonzero;
            }
        }
        inf.readEoln();

        ensuref(nonzero >= 2, "case %d has only %d nonzero digits", caseCount, nonzero);
        // CHECK: the statement has no case-count limit; use the local default cap.
        ensuref(caseCount <= 100000, "too many cases: %d", caseCount);
    }

    ensuref(caseCount > 0, "input must contain at least one problem before the terminator");
    inf.readEof();
}
