#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readEoln();

    inf.readInts(n, -100, 100, "a");
    inf.readEoln();

    inf.readEof();
}
