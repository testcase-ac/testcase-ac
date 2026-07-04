#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 200, "M");
    inf.readSpace();
    int n = inf.readInt(1, 200, "N");
    inf.readEoln();

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 2, "a_i_j");
        }
        inf.readEoln();
    }

    inf.readEof();
}
