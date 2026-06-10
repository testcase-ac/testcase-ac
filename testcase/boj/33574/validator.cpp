#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int q = inf.readInt(1, 3000, "Q");
    inf.readEoln();

    int size = 0;
    for (int i = 1; i <= q; ++i) {
        int type = inf.readInt(1, 2, "type");
        inf.readSpace();

        if (type == 1) {
            inf.readInt(1, 2, "x");
        } else {
            int x = inf.readInt(0, size, "x");
            inf.readSpace();
            inf.readLong(-1000000000LL, 1000000000LL, "t");
            ++size;
        }

        inf.readEoln();
    }

    inf.readEof();
}
