#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 2000000000LL, "P_i");
    inf.readEoln();

    inf.readEof();
}
