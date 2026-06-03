#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 10000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        setTestCase(caseCount);
        // CHECK: The statement does not cap the number of test cases.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);

        inf.readInt(0, 1, "r_i");
        for (int i = 2; i <= n; ++i) {
            inf.readSpace();
            inf.readInt(0, 1, "r_i");
        }
        inf.readEoln();
    }

    inf.readEof();
}
