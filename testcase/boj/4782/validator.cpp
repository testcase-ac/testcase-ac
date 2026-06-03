#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int kMaxValue = 1000000;
    constexpr int kMaxCases = 100000;

    int caseCount = 0;
    while (true) {
        int b = inf.readInt(0, kMaxValue, "b");
        inf.readSpace();
        int n = inf.readInt(0, kMaxValue, "n");
        inf.readEoln();

        if (b == 0 && n == 0) {
            break;
        }

        setTestCase(++caseCount);
        ensuref(1 <= b, "b must be positive before terminator, got %d", b);
        ensuref(1 <= n, "n must be positive before terminator, got %d", n);
        // CHECK: the statement gives no test case count bound; use the local default cap.
        ensuref(caseCount <= kMaxCases, "too many test cases: %d", caseCount);
    }

    inf.readEof();
}
