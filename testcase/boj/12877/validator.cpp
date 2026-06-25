#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "n");
    inf.readSpace();
    int k = inf.readInt(0, 100000, "k");
    inf.readEoln();

    for (int i = 0; i < k; ++i) {
        inf.readInt(1, 2, "t_i");
        inf.readSpace();
        inf.readInt(-2147483647 - 1, 2147483647, "x_i");
        inf.readSpace();
        inf.readInt(-2147483647 - 1, 2147483647, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
