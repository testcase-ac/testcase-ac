#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "C");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "D");
    inf.readEoln();

    inf.readEof();
}
