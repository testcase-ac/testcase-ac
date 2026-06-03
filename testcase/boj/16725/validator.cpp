#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 500, "n");
    inf.readSpace();
    int m = inf.readInt(1, 500, "m");
    inf.readSpace();
    int k = inf.readInt(0, n * m, "k");
    inf.readEoln();
    inf.readEof();
}
