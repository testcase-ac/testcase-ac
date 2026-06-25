#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 750, "R");
    inf.readSpace();
    int c = inf.readInt(2, 750, "C");
    inf.readSpace();
    int k = inf.readInt(1, r * c, "K");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, k, "grid_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
