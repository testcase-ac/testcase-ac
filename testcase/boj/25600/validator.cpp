#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 10000, "a");
        inf.readSpace();
        inf.readInt(0, 10000, "d");
        inf.readSpace();
        inf.readInt(0, 10000, "g");
        inf.readEoln();
    }

    inf.readEof();
}
