#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    inf.readInts(n, 1, 100, "slime_size");
    inf.readEoln();
    inf.readEof();
}
