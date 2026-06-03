#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        int f = inf.readInt(1, n, "f_i");
        inf.readSpace();
        int d = inf.readInt(1, m, "d_i");
        inf.readEoln();
    }

    inf.readEof();
}
