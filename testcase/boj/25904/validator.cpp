#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(3, 100, "N");
    inf.readSpace();
    int X = inf.readInt(1, 100, "X");
    inf.readEoln();

    inf.readInts(N, 1, 200, "T_i");
    inf.readEoln();

    inf.readEof();
}
