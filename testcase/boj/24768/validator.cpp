#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no case count limit; use the local multi-case cap.
    const int maxCases = 100000;
    int cases = 0;

    while (true) {
        int x = inf.readInt(0, 1000, "x");
        inf.readSpace();
        int y = inf.readInt(0, 1000, "y");
        inf.readEoln();

        if (x == 0 && y == 0) {
            break;
        }

        ++cases;
        ensuref(cases <= maxCases, "too many cases: %d", cases);
    }

    inf.readEof();
}
