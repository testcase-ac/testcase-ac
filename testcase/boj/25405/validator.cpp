#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();
    inf.readLongs(n, 1LL, 1000000000LL, "l_i");
    inf.readEoln();
    inf.readInt(1, 1000000000, "m");
    inf.readSpace();
    inf.readInt(1, n, "k");
    inf.readEoln();
    inf.readEof();
}
