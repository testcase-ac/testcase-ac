#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    inf.readInt(0, 100, "k");
    inf.readSpace();
    inf.readInt(0, 100, "T_0");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 100, "d_i");
    }
    inf.readEoln();
    inf.readEof();
}
