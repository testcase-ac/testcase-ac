#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(5, 20, "N");
    inf.readSpace();
    inf.readInt(0, 3, "K");
    inf.readEoln();

    inf.readInts(n, 1, 5, "answer");
    inf.readEoln();

    inf.readInts(n, 1, 5, "omr");
    inf.readEoln();

    inf.readEof();
}
