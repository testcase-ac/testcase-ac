#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "C");
    inf.readSpace();
    int q = inf.readInt(1, 10000, "Q");
    inf.readEoln();

    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            inf.readInt(1, 1000, "K");
        }
        inf.readEoln();
    }

    for (int i = 0; i < q; ++i) {
        int r1 = inf.readInt(1, r, "r_1");
        inf.readSpace();
        int c1 = inf.readInt(1, c, "c_1");
        inf.readSpace();
        int r2 = inf.readInt(r1, r, "r_2");
        inf.readSpace();
        inf.readInt(c1, c, "c_2");
        inf.readEoln();
    }

    inf.readEof();
}
