#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 100, "W_i_j");
        }
        inf.readEoln();
    }

    inf.readInt(0, n - 1, "x");
    inf.readSpace();
    inf.readInt(0, m - 1, "y");
    inf.readSpace();
    inf.readInt(0, 20, "p");
    inf.readEoln();

    inf.readEof();
}
