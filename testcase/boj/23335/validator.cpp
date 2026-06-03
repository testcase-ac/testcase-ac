#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 1000000, "T");
    inf.readEoln();

    for (int i = 1; i <= t; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(1, 1000000, "n_i");
    }
    inf.readEoln();
    inf.readEof();
}
