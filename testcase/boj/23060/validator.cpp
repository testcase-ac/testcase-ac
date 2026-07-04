#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    inf.readInt(1, n, "r");
    inf.readSpace();
    inf.readInt(1, n, "c");
    inf.readEoln();

    inf.readEof();
}
