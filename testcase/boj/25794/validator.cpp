#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(0, 1000000, "X");
    inf.readSpace();
    int y = inf.readInt(0, 1000000, "Y");
    inf.readEoln();

    ensuref(x != 0 || y != 0, "X and Y must not both be zero");

    inf.readEof();
}
