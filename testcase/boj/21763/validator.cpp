#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    inf.readInt(0, n * n, "k");
    inf.readEoln();
    inf.readEof();
}
