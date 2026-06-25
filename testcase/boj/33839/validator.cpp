#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, -10000, 10000, "A");
    inf.readEoln();
    inf.readEof();
}
