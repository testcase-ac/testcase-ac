#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000000, "n");
    inf.readSpace();
    int p = inf.readInt(2, n, "p");
    inf.readEoln();
    inf.readEof();
}
