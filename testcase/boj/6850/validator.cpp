#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000, 1000, "x");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y");
        inf.readEoln();
    }

    // CHECK: the statement gives tree coordinates but does not require unique coordinate pairs.
    inf.readEof();
}
