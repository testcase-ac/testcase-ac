#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    long long sejunX = inf.readLong(0LL, 1000000000LL, "SejunX");
    inf.readSpace();
    long long sejunY = inf.readLong(0LL, 1000000000LL, "SejunY");
    inf.readSpace();
    long long mineX = inf.readLong(0LL, 1000000000LL, "mineX");
    inf.readSpace();
    long long mineY = inf.readLong(0LL, 1000000000LL, "mineY");
    inf.readEoln();
    inf.readEof();

    (void)n;
    (void)sejunX;
    (void)sejunY;
    (void)mineX;
    (void)mineY;
}
