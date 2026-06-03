#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50, "n");
    inf.readSpace();
    int m = inf.readInt(2, n - 1, "m");
    inf.readEoln();
    inf.readEof();
}
