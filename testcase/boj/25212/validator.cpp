#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10, "N");
    inf.readEoln();

    inf.readInts(n, 2, 25, "c_i");
    inf.readEoln();

    inf.readEof();
}
