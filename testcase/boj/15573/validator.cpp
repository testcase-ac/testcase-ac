#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 1000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n * m, "K");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000000, "S_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
