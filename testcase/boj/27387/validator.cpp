#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(0, 1000, "m");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, n - 1, "a");
        inf.readEoln();
    }

    inf.readEof();
}
