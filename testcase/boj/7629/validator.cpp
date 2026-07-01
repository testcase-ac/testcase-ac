#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 1000, "N");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        // CHECK: The statement gives no number-of-cases bound, so cap sentinel
        // input at a practical size while preserving independent test cases.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
    }

    ensuref(caseCount > 0, "input must contain at least one test case before 0");
    inf.readEof();
}
