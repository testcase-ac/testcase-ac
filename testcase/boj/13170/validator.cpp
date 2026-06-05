#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, n, "K");
    inf.readSpace();
    int p = inf.readInt(1, 2000, "P");
    inf.readSpace();
    inf.readInt(1, p, "W");
    inf.readEoln();
    inf.readEof();
}
