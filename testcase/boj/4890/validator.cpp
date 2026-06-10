#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int testCount = 0;
    while (true) {
        int w = inf.readInt(0, 999999, "W");
        inf.readSpace();
        int h = inf.readInt(0, 999999, "H");
        inf.readEoln();

        if (w == 0 && h == 0) {
            break;
        }

        ensuref(w > 0 && h > 0, "non-terminating tile dimensions must be positive: W=%d H=%d", w, h);
        ++testCount;
        // CHECK: The statement has no testcase-count bound; use the local default cap.
        ensuref(testCount <= 100000, "too many test cases: %d", testCount);
    }

    ensuref(testCount >= 1, "input must contain at least one data set before 0 0");
    inf.readEof();
}
