#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 80, "N");
    inf.readEoln();

    inf.readInts(n, -1000000, 1000000, "A");
    inf.readEoln();

    inf.readEof();
}
