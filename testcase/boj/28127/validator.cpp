#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 500000, "Q");
    inf.readEoln();

    for (int i = 0; i < q; ++i) {
        inf.readInt(1, 1000000, "a");
        inf.readSpace();
        inf.readInt(1, 1000000, "d");
        inf.readSpace();
        inf.readInt(1, 1000000, "x");
        inf.readEoln();
    }

    inf.readEof();
}
