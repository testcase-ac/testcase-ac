#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int h = inf.readInt(1, 1000, "H");
    inf.readSpace();
    int w = inf.readInt(1, 1000, "W");
    inf.readSpace();
    int s = inf.readInt(1, h * w, "S");
    inf.readEoln();

    for (int i = 1; i <= h; ++i) {
        for (int j = 1; j <= w; ++j) {
            inf.readInt(1, 256, "A_i_j");
            if (j == w) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
