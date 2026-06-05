#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    inf.readInts(n, 0, 100000, "a");
    inf.readEoln();

    inf.readEof();
}
