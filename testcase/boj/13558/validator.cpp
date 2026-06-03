#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readEoln();

    inf.readInts(n, 1, 30000, "A_i");
    inf.readEoln();
    inf.readEof();
}
