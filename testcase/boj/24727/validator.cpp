#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readInt(1, n * n, "C");
    inf.readSpace();
    inf.readInt(1, n * n, "E");
    inf.readEoln();

    inf.readEof();
}
