#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    inf.readInt(0, 1000, "a");
    inf.readSpace();
    inf.readInt(0, 1000, "b");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        // CHECK: The statement gives cow locations only as per-cow positions and
        // does not require them to be distinct or sorted.
        inf.readInt(0, 1000000, "x_i");
        inf.readEoln();
    }

    inf.readEof();
}
