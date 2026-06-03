#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "K");
    inf.readEoln();

    inf.readLongs(n, 0LL, 1000000000LL, "A");
    inf.readEoln();
    inf.readEof();
}
