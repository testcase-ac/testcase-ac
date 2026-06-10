#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000000, "m");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 100000000, "a");
        inf.readSpace();
        inf.readInt(1, 100000000, "s");
        inf.readEoln();
    }

    inf.readEof();
}
