#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readInt(1, 10000, "W_i");
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
