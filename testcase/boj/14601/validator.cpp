#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 7, "K");
    inf.readEoln();

    int side = 1 << k;
    inf.readInt(1, side, "x");
    inf.readSpace();
    inf.readInt(1, side, "y");
    inf.readEoln();

    inf.readEof();
}
