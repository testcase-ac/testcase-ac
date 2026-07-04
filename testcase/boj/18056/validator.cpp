#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readSpace();
    inf.readInt(1, n, "c");
    inf.readSpace();
    int y = inf.readInt(n - 1, 1000000000, "y");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(n - 1, 1000000000, "x_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
