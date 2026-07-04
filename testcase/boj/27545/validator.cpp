#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 500000, "H");
    inf.readSpace();
    int w = inf.readInt(2, 500000, "W");
    inf.readEoln();

    ensuref(1LL * h * w <= 500000LL, "H * W must be at most 500000, got %lld",
            1LL * h * w);

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000000000, "A_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
