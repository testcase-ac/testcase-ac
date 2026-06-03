#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long L = inf.readLong(2LL, 1000000000LL, "L");
    inf.readSpace();
    int K = inf.readInt(1, 10000, "K");
    inf.readSpace();
    inf.readInt(1, 10000, "C");
    inf.readEoln();

    inf.readLongs(K, 1LL, L, "position");
    inf.readEoln();

    inf.readEof();
}
