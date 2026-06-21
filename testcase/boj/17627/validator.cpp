#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int q = inf.readInt(1, 200000, "q");
    inf.readEoln();

    inf.readInts(n, 0, 1000000000, "a_i");
    inf.readEoln();

    for (int action = 1; action <= q; ++action) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            int i = inf.readInt(1, n, "i");
            inf.readSpace();
            inf.readInt(0, 1000000000, "j");
        } else {
            int l = inf.readInt(1, n, "l");
            inf.readSpace();
            int u = inf.readInt(l, n, "u");
        }

        inf.readEoln();
    }

    inf.readEof();
}
