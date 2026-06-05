#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100, "m");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(1, 100000, "w_i");
        inf.readSpace();
        inf.readInt(0, 1000, "v_i");
        inf.readEoln();
    }

    for (int i = 0; i < m; ++i) {
        inf.readInt(1, 1000000, "k_i");
        inf.readEoln();
    }

    inf.readEof();
}
