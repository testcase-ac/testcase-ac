#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        // CHECK: The statement only says N <= 24 and uses 0 as the sentinel,
        // so real test cases require at least one mansion.
        int n = inf.readInt(0, 24, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        // CHECK: The statement does not bound the number of test cases.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
        setTestCase(caseCount);

        for (int i = 0; i < n; ++i) {
            inf.readInt(1000000, 40000000, "value");
            inf.readEoln();
        }
    }

    inf.readEof();
}
