#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readEoln();

    inf.readLong(1LL, 1000000000LL, "a_i");
    for (int i = 2; i <= n; ++i) {
        inf.readSpace();
        inf.readLong(1LL, 1000000000LL, "a_i");
    }
    inf.readEoln();
    inf.readEof();
}
