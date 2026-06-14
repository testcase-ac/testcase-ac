#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 1000000000, "A_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
