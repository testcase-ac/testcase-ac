#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long l = inf.readLong(1LL, 1000000000000LL, "L");
    inf.readSpace();
    long long r = inf.readLong(l, 1000000000000LL, "R");
    inf.readEoln();
    inf.readEof();
}
