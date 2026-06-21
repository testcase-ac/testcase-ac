#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 1000000, "X");
    inf.readSpace();
    int y = inf.readInt(1, 1000000, "Y");
    inf.readEoln();

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readDouble(0.0, x, "x_i");
        inf.readSpace();
        inf.readDouble(0.0, y, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
