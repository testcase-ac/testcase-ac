#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 1000000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ensuref(n >= 5, "n must be either 0 or in [5, 1000000], got %d", n);
        ++caseCount;

        // CHECK: the statement does not bound the number of input lines.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
    }

    ensuref(caseCount > 0, "input must contain at least one test case before 0");
    inf.readEof();
}
