#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readEoln();

    inf.readInts(n, 0, 10000, "score");
    inf.readEoln();

    inf.readEof();
}
