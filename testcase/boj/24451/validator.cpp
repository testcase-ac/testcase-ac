#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 3000, "N");
    inf.readSpace();
    int k = inf.readInt(2, n, "K");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "A_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
