#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100000, "n");
    inf.readEoln();

    for (int i = 2; i <= n; ++i) {
        if (i > 2) {
            inf.readSpace();
        }
        inf.readInt(1, i - 1, "p_i");
    }
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(0, 100000, "a_i");
    }
    inf.readEoln();

    inf.readEof();
}
