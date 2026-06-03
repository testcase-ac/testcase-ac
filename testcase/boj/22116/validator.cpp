#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readEoln();

    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            inf.readLong(1LL, 1000000000LL, "a_rc");
            if (c == n) {
                inf.readEoln();
            } else {
                inf.readSpace();
            }
        }
    }

    inf.readEof();
}
