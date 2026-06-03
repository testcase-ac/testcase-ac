#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(2, 10, "M");
    inf.readSpace();
    int n = inf.readInt(3, 100, "N");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInts(n, 1, 10000, "planet_size");
        inf.readEoln();
    }

    inf.readEof();
}
