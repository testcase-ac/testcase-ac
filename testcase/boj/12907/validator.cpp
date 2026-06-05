#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 40, "n");
    inf.readEoln();

    inf.readInts(n, 0, 40, "answers");
    inf.readEoln();

    inf.readEof();
}
