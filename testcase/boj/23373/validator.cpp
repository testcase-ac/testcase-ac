#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 300, "n");
    inf.readEoln();

    inf.readInts(n, 1, 1000, "w");
    inf.readEoln();

    inf.readEof();
}
