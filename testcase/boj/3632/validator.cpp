#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000000000, "a");
    inf.readEoln();

    inf.readInt(1, 1000000000, "k");
    inf.readEoln();

    inf.readEof();
}
