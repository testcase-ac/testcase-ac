#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 10, "n");
    inf.readSpace();
    inf.readInt(0, 1000, "m");
    inf.readSpace();
    inf.readInt(1, 4, "k");
    inf.readEoln();

    inf.readInts(n, 100, 1000, "p_i");
    inf.readEoln();
    inf.readEof();
}
