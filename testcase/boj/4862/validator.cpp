#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no test case count limit; use the local default cap.
    constexpr int MAX_TEST_CASES = 100000;

    int testCase = 0;
    while (true) {
        int b = inf.readInt(0, 100, "b");
        inf.readEoln();

        if (b == 0) {
            break;
        }

        ++testCase;
        setTestCase(testCase);
        ensuref(testCase <= MAX_TEST_CASES, "too many test cases: %d", testCase);

        inf.readInt(1, 100, "i");
        inf.readEoln();
        inf.readInt(1, 7, "n");
        inf.readEoln();
    }

    inf.readEof();
}
