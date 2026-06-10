#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInts(n, 0, 1000000, "height");
        inf.readEoln();
    }

    inf.readEof();
}
