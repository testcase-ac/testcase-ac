#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000000, "a");
    inf.readEoln();
    inf.readEof();
}
