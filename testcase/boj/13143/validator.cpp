#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int s = inf.readInt(1, 9999, "S_i");
        inf.readSpace();
        int h = inf.readInt(2, 10000, "H_i");
        inf.readEoln();

        ensuref(s < h, "expected S_i < H_i at index %d, got %d %d", i, s, h);
    }

    inf.readEof();
}
