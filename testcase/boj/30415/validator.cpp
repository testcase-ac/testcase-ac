#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readSpace();
    inf.readInt(2, n, "m");
    inf.readEoln();

    inf.readEof();
}
