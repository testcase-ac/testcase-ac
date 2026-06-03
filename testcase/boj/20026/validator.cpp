#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 100, "N");
    inf.readEoln();

    int m = n * (n - 1) / 2;
    inf.readLongs(m, 1LL, 2000000000LL, "C_i");
    inf.readEoln();

    inf.readEof();
}
