#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, 1, 9, "A_i");
    inf.readEoln();
    inf.readEof();
}
