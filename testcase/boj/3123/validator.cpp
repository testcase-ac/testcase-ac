#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int x_limit = inf.readInt(1, 1000, "X");
    inf.readSpace();
    int y_limit = inf.readInt(1, 1000, "Y");
    inf.readEoln();

    int n = inf.readInt(1, 10000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int x = inf.readInt(0, x_limit, "x_i");
        inf.readSpace();
        int y = inf.readInt(0, y_limit, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
