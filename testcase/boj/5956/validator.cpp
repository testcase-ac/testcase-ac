#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: The available statement text omits explicit bounds for grid dimensions.
    // Use a practical cap that keeps the recursive cow count within signed 64-bit.
    int n = inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000000000, "M");
    inf.readEoln();

    inf.readEof();
}
