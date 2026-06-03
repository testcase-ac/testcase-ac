#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int cases = 0;
    while (true) {
        int n = inf.readInt(0, 1000000, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        ensuref(n >= 1, "n must be positive before the terminating zero");
        ++cases;
        // CHECK: The statement gives no testcase-count limit, so use the local default cap.
        ensuref(cases <= 100000, "too many test cases: %d", cases);
    }

    inf.readEof();
}
