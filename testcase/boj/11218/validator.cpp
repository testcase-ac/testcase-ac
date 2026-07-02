#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 30, "n");
    inf.readEoln();

    for (int i = 2; i <= n; ++i) {
        inf.readLong(0LL, 1000000000LL, "a_i");
        if (i == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }

    inf.readEof();
}
