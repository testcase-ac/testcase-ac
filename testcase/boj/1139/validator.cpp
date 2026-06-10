#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 16, "n");
    inf.readEoln();

    inf.readInts(n, 1, 100, "length");
    inf.readEoln();

    inf.readEof();
}
