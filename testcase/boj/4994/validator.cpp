#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int caseCount = 0;
    while (true) {
        int n = inf.readInt(0, 200, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ++caseCount;
        // CHECK: The statement has no test case count bound; cap it by local policy.
        ensuref(caseCount <= 100000, "too many test cases: %d", caseCount);
    }

    inf.readEof();
}
