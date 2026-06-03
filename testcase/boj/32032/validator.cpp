#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    inf.readInt(1, 1000000000, "d");
    inf.readEoln();

    inf.readLongs(n, -1000000000LL, 1000000000LL, "x_i");
    inf.readEoln();
    inf.readEof();
}
