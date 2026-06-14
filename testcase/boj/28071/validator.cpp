#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    inf.readInt(1, 300, "M");
    inf.readSpace();
    inf.readInt(1, 300, "K");
    inf.readEoln();

    inf.readInts(n, 1, 300, "a_i");
    inf.readEoln();
    inf.readEof();
}
