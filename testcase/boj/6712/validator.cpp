#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 100, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int xL = inf.readInt(0, 2000000000, "x_L");
        inf.readSpace();
        int xH = inf.readInt(xL, 2000000000, "x_H");
        inf.readEoln();
    }

    inf.readEof();
}
