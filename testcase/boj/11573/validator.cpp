#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement gives no upper bound for T; use the local default cap.
    int t = inf.readInt(1, 100000, "T");
    inf.readEoln();

    for (int tc = 1; tc <= t; ++tc) {
        setTestCase(tc);

        inf.readInt(1, 100, "r");
        inf.readSpace();
        inf.readInt(1, 100, "y");
        inf.readSpace();
        inf.readInt(1, 100, "b");
        inf.readEoln();
    }

    inf.readEof();
}
