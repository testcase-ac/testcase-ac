#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-10000, 10000, "x_i");
        inf.readSpace();
        inf.readInt(-10000, 10000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
