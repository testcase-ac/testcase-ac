#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "x_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "y_i");
    inf.readEoln();

    inf.readEof();
}
