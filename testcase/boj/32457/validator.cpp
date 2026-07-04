#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 18, "n");
    inf.readEoln();

    for (int i = 1; i < n; ++i) {
        inf.readInt(1, 10000, "b_i");
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
