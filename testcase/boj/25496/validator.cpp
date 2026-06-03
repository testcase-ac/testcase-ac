#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int p = inf.readInt(1, 200, "p");
    inf.readSpace();
    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 200, "a_i");
    inf.readEoln();
    inf.readEof();
}
