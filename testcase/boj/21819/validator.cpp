#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int k = inf.readInt(0, 100000, "K");
    inf.readSpace();
    int l = inf.readInt(0, 100000, "L");
    inf.readEoln();

    inf.readInts(n, 0, 100000, "c_i");
    inf.readEoln();

    inf.readEof();
}
