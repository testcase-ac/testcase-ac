#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 200000, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readEof();
}
