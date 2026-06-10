#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(0, 9, "w_ij");
        }
        inf.readEoln();
    }

    int k = inf.readInt(1, 100000, "k");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        inf.readInt(1, 9, "d_i");
    }
    inf.readEoln();

    inf.readEof();
}
