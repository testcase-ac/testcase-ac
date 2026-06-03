#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(2LL, 1000000000000LL, "L");
    inf.readSpace();
    inf.readLong(l, 1000000000000LL, "H");
    inf.readEoln();
    inf.readEof();

    return 0;
}
