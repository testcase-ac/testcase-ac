#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int L = inf.readInt(1, 50000, "L");
    inf.readSpace();
    int W = inf.readInt(1, 50000, "W");
    inf.readSpace();
    int N = inf.readInt(1, 250, "N");
    inf.readEoln();

    for (int i = 0; i < N; ++i) {
        inf.readInt(0, L, "X_i");
        inf.readSpace();
        inf.readInt(0, W, "Y_i");
        inf.readEoln();
    }

    inf.readEof();
}
