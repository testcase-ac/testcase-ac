#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The statement does not give an upper bound for n; use the local default cap.
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        setTestCase(i);

        inf.readInt(1, 100, "s");
        inf.readSpace();
        inf.readInt(1, 100, "r");
        inf.readEoln();
    }

    inf.readEof();
}
