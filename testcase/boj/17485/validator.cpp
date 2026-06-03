#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 1000, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInts(m, 1, 100, "fuel");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
