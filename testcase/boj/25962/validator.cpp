#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(1LL, 1000000000000000000LL, "N");
    inf.readSpace();
    int m = inf.readInt(2, 100000, "M");
    inf.readEoln();

    for (int i = 1; i <= m; ++i) {
        inf.readInt(1, 5, "t_i");
        inf.readEoln();
    }

    inf.readEof();
}
