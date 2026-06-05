#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(0, n, "k");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "h_i");
    inf.readEoln();

    inf.readEof();
}
