#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "cow_height");
    inf.readEoln();

    inf.readLongs(m, 1LL, 1000000000LL, "candy_height");
    inf.readEoln();

    inf.readEof();
}
