#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int p = inf.readInt(4, 2 * (n + m), "p");
    inf.readEoln();

    inf.readEof();
}
