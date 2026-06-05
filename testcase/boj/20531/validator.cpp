#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        int x = inf.readInt(1, n, "x_i");
        inf.readSpace();
        int y = inf.readInt(1, n, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
