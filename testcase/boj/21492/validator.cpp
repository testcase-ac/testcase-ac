#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 100000, "n");
    inf.readSpace();
    inf.readInt(1, n / 3, "k");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        if (i > 1) {
            inf.readSpace();
        }
        inf.readLong(1LL, 1000000000LL, "a_i");
    }
    inf.readEoln();

    inf.readEof();
}
