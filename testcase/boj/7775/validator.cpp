#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    int p = inf.readInt(0, 1000000, "p");
    inf.readSpace();
    int k = inf.readInt(1, n, "k");
    inf.readSpace();
    int d = inf.readInt(1, k, "d");
    inf.readEoln();
    inf.readEof();
}
