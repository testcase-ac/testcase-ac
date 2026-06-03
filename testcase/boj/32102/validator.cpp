#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(2, 2000, "M");
    inf.readEoln();

    long long cells = 1LL * n * m;
    long long r = inf.readLong(1LL, cells, "R");
    inf.readSpace();
    long long g = inf.readLong(1LL, cells, "G");
    inf.readSpace();
    long long b = inf.readLong(1LL, cells, "B");
    inf.readEoln();

    ensuref(r + g + b == cells, "R + G + B must equal N * M");

    inf.readEof();
}
