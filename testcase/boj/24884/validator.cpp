#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 6, "N");
    inf.readSpace();
    inf.readInt(0, n - 1, "W");
    inf.readSpace();
    inf.readInt(1, 11, "T");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, 0, 50, "F_i");
    inf.readEoln();

    inf.readEof();
}
