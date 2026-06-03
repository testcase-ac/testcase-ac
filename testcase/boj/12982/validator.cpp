#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 100000, "K");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        inf.readLong(1LL, 1000000000LL, "X_i");
        if (i < k) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
}
