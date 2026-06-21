#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "n");
    inf.readEoln();

    // CHECK: The statement does not require cow coordinates to be distinct or
    // exclude the origin, so this validator accepts any point within bounds.
    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
