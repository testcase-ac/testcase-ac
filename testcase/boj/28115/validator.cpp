#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readLong(-1000000000LL, 1000000000LL, "A_1");
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        inf.readLong(-1000000000LL, 1000000000LL, "A_i");
    }
    inf.readEoln();

    inf.readEof();
}
