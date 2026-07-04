#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "t");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "w_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "d_j");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "p_j");
    inf.readEoln();

    inf.readEof();
}
