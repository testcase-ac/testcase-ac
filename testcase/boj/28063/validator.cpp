#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readEoln();

    inf.readInt(1, n, "x");
    inf.readSpace();
    inf.readInt(1, n, "y");
    inf.readEoln();

    inf.readEof();
}
