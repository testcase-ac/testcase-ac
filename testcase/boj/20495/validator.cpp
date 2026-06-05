#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 500000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(-1000000000LL, 1000000000LL, "a_i");
        inf.readSpace();
        inf.readLong(0LL, 1000000000LL, "b_i");
        inf.readEoln();
    }

    inf.readEof();
}
