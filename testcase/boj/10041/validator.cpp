#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(2, 10000, "W");
    inf.readSpace();
    int h = inf.readInt(2, 10000, "H");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, w, "X_i");
        inf.readSpace();
        inf.readInt(1, h, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
