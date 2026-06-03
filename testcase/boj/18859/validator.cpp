#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 402000, "N");
    inf.readEoln();

    inf.readLongs(n, 1LL, 1000000000LL, "a");
    inf.readEoln();

    inf.readEof();
}
