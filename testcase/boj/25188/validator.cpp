#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readEoln();

    inf.readLongs(n, -1000000000LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readEof();
}
