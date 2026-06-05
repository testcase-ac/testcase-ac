#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 300000, "N");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "A_i");
    inf.readEoln();
    inf.readEof();
}
