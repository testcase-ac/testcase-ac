#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5000, "N");
    inf.readSpace();
    int k = inf.readInt(0, n, "K");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "B_i");
    inf.readEoln();

    inf.readEof();
}
