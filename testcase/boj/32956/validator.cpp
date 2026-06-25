#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, 1000000000LL, "A_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
