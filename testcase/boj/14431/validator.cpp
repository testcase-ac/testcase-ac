#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(-3000, 3000, "x1");
    inf.readSpace();
    inf.readInt(-3000, 3000, "y1");
    inf.readSpace();
    inf.readInt(-3000, 3000, "x2");
    inf.readSpace();
    inf.readInt(-3000, 3000, "y2");
    inf.readEoln();

    int n = inf.readInt(0, 4000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-3000, 3000, "x_i");
        inf.readSpace();
        inf.readInt(-3000, 3000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
