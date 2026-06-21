#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 10000, "M");
    inf.readSpace();
    long long k = inf.readLong(0LL, 1LL * n * m, "K");
    inf.readEoln();

    inf.readEof();
}
