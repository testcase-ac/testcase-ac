#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "m");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readSpace();
        inf.readInt(-1000, 1000, "w");
        inf.readEoln();
    }

    inf.readEof();
}
