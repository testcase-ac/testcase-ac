#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "N");
    inf.readSpace();
    inf.readInt(1, 100, "K");
    inf.readEoln();

    inf.readInts(n, 0, 100, "a_i");
    inf.readEoln();
    inf.readEof();
}
