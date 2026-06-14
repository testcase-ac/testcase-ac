#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "A");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(-1000, 1000, "x_i");
        inf.readSpace();
        inf.readInt(-1000, 1000, "y_i");
        inf.readSpace();
        inf.readInt(1, 200, "w_i");
        inf.readEoln();
    }

    inf.readEof();
}
