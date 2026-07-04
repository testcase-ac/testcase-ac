#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "a_i");
    }
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(0, 1, "b_i");
    }
    inf.readEoln();

    inf.readEof();
}
