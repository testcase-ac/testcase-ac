#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(-2000, 2000, "value");
        inf.readEoln();
    }

    inf.readEof();
}
