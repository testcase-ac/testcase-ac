#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int d = inf.readInt(1, 1000000, "d");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1000000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
