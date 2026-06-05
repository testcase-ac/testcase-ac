#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 1000000, "n");
    inf.readEoln();

    inf.readInts(n, -100000, 100000, "a");
    inf.readEoln();

    inf.readEof();
}
