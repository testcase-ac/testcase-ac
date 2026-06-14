#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(-1000, 1000, "x1");
    inf.readSpace();
    inf.readInt(-1000, 1000, "y1");
    inf.readSpace();
    inf.readInt(-1000, 1000, "z1");
    inf.readSpace();
    inf.readInt(-1000, 1000, "x2");
    inf.readSpace();
    inf.readInt(-1000, 1000, "y2");
    inf.readSpace();
    inf.readInt(-1000, 1000, "z2");
    inf.readEoln();

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 100, "k");
    }
    inf.readEoln();

    inf.readEof();
}
