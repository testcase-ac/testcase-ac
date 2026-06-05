#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int queryCount = 0;
    while (true) {
        int i = inf.readInt(-1, 1000000, "i");
        inf.readEoln();

        if (i == -1) {
            break;
        }

        ensuref(i >= 0, "query value must be nonnegative: %d", i);
        ++queryCount;
        // CHECK: The statement has no testcase-count limit; use the local default cap.
        ensuref(queryCount <= 100000, "too many query lines: %d", queryCount);
    }

    inf.readEof();
}
