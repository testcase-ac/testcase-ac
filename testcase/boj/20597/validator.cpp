#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readSpace();
    int k = inf.readInt(0, n * (n - 1) / 2, "k");
    inf.readEoln();
    inf.readEof();
}
