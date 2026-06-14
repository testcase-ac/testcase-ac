#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 20000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 500, "M");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 125000000, "X_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
