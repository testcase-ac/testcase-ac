#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 60, "N");
    inf.readSpace();

    long long limit = 1LL << n;
    inf.readLong(1LL, limit, "P");
    inf.readSpace();
    inf.readLong(1LL, limit, "H");
    inf.readEoln();

    inf.readEof();
    return 0;
}
