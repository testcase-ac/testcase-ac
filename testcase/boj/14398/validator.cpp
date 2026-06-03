#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "N");
    inf.readEoln();

    inf.readInts(n, 1, 999999, "length");
    inf.readEoln();

    inf.readEof();
}
