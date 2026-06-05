#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x = inf.readInt(1, 100000, "X");
    inf.readSpace();
    int k = inf.readInt(1, 10000, "K");
    inf.readEoln();

    inf.readInts(2 * x, 1, k, "A_i");
    inf.readEoln();
    inf.readEof();
}
