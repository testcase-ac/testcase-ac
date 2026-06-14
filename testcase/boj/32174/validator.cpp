#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int type = inf.readInt(1, 3, "type");
        inf.readSpace();

        if (type == 1) {
            inf.readLong(1LL, 1000000000000000000LL, "x_i");
        } else if (type == 2) {
            inf.readLong(1LL, 1000000000000000000LL, "y_i");
        } else {
            inf.readInt(0, i - 1, "z_i");
        }

        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
