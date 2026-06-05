#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readInt(-1000, 1000, "A_i");
    }
    inf.readEoln();

    inf.readEof();
}
