#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long h = inf.readLong(3LL, 1000000000LL, "H");
    inf.readSpace();
    long long w = inf.readLong(3LL, 1000000000LL, "W");
    inf.readEoln();

    int n = inf.readInt(1, 60000, "N");
    inf.readEoln();

    for (int i = 1; i <= n; ++i) {
        inf.readLong(1LL, h, "A_i");
        inf.readSpace();
        inf.readLong(1LL, w, "B_i");
        inf.readEoln();
    }

    inf.readEof();
}
