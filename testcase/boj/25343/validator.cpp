#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    for (int row = 0; row < n; ++row) {
        for (int col = 0; col < n; ++col) {
            inf.readInt(1, 10000, "A_i_j");
            if (col + 1 < n) {
                inf.readSpace();
            }
        }
        inf.readEoln();
    }

    inf.readEof();
}
