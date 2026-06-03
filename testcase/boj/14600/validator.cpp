#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 2, "K");
    inf.readEoln();

    int n = 1 << k;
    inf.readInt(1, n, "x");
    inf.readSpace();
    inf.readInt(1, n, "y");
    inf.readEoln();

    inf.readEof();
}
