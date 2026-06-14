#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 1000, "M");
    inf.readEoln();
    int n = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int r = 1; r <= m; ++r) {
        for (int c = 1; c <= n; ++c) {
            inf.readInt(1, 1000000, "cell");
            if (c < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
