#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    inf.readInt(0, 1000, "x_0");
    inf.readSpace();
    inf.readInt(0, 1000, "y_0");
    inf.readSpace();
    inf.readInt(1, 1000000, "E_0");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(0, 1000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1000, "y_i");
        inf.readSpace();
        inf.readInt(0, 1000, "E_i");
        inf.readEoln();
    }

    inf.readEof();
}
