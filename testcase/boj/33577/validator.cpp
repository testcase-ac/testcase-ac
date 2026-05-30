#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    inf.readLongs(N, 1LL, 1000000000LL, "A");
    inf.readEoln();

    inf.readEof();
}
