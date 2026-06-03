#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "n");
    inf.readSpace();
    inf.readInt(1, 1000, "m");
    inf.readSpace();
    int k = inf.readInt(1, n - 1, "k");
    inf.readEoln();
    inf.readEof();
}
