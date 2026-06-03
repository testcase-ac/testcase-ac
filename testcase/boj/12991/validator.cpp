#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 30000, "n");
    inf.readSpace();
    long long k = inf.readLong(1LL, 1LL * n * n, "k");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "b_i");
    inf.readEoln();

    inf.readEof();
}
