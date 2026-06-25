#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 4000000, "N");
    ensuref(n % 2 == 0, "N must be a multiple of 2: %d", n);
    inf.readEoln();

    int half = n / 2;
    for (int i = 1; i <= half; ++i) {
        int remaining = n - 2 * (i - 1);
        inf.readInt(1, remaining, "a_i");
        if (i < half) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    for (int i = 1; i <= half; ++i) {
        int remaining = n - (2 * i - 1);
        inf.readInt(1, remaining, "b_i");
        if (i < half) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
