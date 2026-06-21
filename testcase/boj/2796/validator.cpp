#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 200000, "x");
        inf.readSpace();
        inf.readInt(0, 200000, "y");
        inf.readSpace();
        inf.readInt(0, 200000, "p");
        inf.readEoln();
    }

    inf.readEof();
}
