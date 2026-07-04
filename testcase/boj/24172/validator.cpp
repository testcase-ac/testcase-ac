#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 300, "N");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "M");
    inf.readEoln();

    inf.readLongs(m, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    inf.readLongs(m, 1LL, 1000000000LL, "B_j");
    inf.readEoln();

    inf.readEof();
}
