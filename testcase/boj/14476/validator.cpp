#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(4, 1000000, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 2000000000LL, "A_i");
    inf.readEoln();
    inf.readEof();
}
