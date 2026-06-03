#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 100, "R");
    inf.readSpace();
    int c = inf.readInt(2, 100, "C");
    inf.readSpace();
    int k = inf.readInt(1, r * c, "K");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            inf.readInt(1, k, "grid_value");
            if (j + 1 < c) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
