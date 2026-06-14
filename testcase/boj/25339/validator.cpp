#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(2LL, 1000000000LL, "N");
    inf.readSpace();
    int q = inf.readInt(1, 100000, "Q");
    inf.readEoln();

    for (int i = 1; i <= q; ++i) {
        int a = inf.readInt(1, 2, "a");
        inf.readSpace();
        long long l = inf.readLong(1LL, n - 1, "l");
        inf.readSpace();
        long long r = inf.readLong(l + 1, n, "r");
        inf.readEoln();
    }

    inf.readEof();
}
