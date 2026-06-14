#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCaseCount = 0;
    while (!inf.eof()) {
        ++testCaseCount;
        setTestCase(testCaseCount);

        inf.readInt(0, 999999999, "N");
        inf.readEoln();

        // CHECK: The statement has no explicit test case count limit; use the local default cap.
        ensuref(testCaseCount <= 100000, "too many test cases: %d", testCaseCount);
    }

    ensuref(testCaseCount > 0, "input must contain at least one test case");
    inf.readEof();
}
