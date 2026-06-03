#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "N");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-1000000, 1000000, "x");
        inf.readSpace();
        inf.readInt(1, 10000, "r");
        inf.readEoln();
    }

    inf.readEof();
}
