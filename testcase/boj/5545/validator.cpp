#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readInt(1, 1000, "A");
    inf.readSpace();
    inf.readInt(1, 1000, "B");
    inf.readEoln();

    inf.readInt(1, 10000, "C");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 10000, "D_i");
        inf.readEoln();
    }

    inf.readEof();
}
