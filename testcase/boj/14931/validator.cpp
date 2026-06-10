#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int l = inf.readInt(1, 1000000, "L");
    inf.readEoln();

    inf.readInts(l, -50000, 50000, "score");
    inf.readEoln();

    inf.readEof();
}
