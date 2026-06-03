#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(0, 1000000, "N");
    inf.readSpace();
    inf.readInt(0, n, "a");
    inf.readSpace();
    inf.readInt(0, n, "b");
    inf.readEoln();
    inf.readEof();
}
