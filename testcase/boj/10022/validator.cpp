#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readSpace();
    int k = inf.readInt(0, 2 * n, "K");
    inf.readEoln();

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            inf.readInt(0, 1000, "G_rc");
            if (c < n) {
                inf.readSpace();
            } else {
                inf.readEoln();
            }
        }
    }

    inf.readEof();
}
