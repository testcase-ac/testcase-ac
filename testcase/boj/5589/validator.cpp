#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 10, "R");
    inf.readSpace();
    int c = inf.readInt(1, 10000, "C");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            inf.readInt(0, 1, "a_i_j");
            if (j + 1 == c) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
