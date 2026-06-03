#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int x = inf.readInt(1, 100, "X");
    inf.readSpace();
    int y = inf.readInt(1, 100, "Y");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        int xi = inf.readInt(1, 100, "x_i");
        inf.readSpace();
        int yi = inf.readInt(1, 100, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
