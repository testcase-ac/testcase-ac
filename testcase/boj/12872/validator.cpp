#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readSpace();
    int m = inf.readInt(0, n, "M");
    inf.readSpace();
    inf.readInt(n, 100, "P");
    inf.readEoln();
    inf.readEof();
}
