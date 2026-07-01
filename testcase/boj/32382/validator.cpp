#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readInts(n, 1, 20, "A_i");
    inf.readEoln();

    inf.readEof();
}
