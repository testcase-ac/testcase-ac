#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
