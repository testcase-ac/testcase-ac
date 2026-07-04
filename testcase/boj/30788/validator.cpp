#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    inf.readInts(n, 0, 179, "A_i");
    inf.readEoln();
    inf.readEof();
}
