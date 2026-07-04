#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    inf.readInt(0, n, "k");
    inf.readEoln();
    inf.readEof();
}
