#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 4242, "N");
    inf.readSpace();
    long long maxK = 1LL * n * (n - 1) / 2;
    inf.readLong(0LL, maxK, "K");
    inf.readEoln();
    inf.readEof();
}
