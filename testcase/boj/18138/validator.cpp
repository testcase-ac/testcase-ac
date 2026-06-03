#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 1000, "shirt_width");
        inf.readEoln();
    }

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, 1000, "collar_width");
        inf.readEoln();
    }

    inf.readEof();
}
