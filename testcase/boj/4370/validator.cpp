#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (!inf.eof()) {
        ++cases;
        setTestCase(cases);

        inf.readLong(2LL, 4294967294LL, "n");
        inf.readEoln();

        // CHECK: The statement gives no testcase-count bound; use the local default cap.
        ensuref(cases <= 100000, "too many test cases: %d", cases);
    }

    ensuref(cases >= 1, "input must contain at least one test case");
    inf.readEof();
}
