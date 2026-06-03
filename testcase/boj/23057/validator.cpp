#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readEoln();

    inf.readLongs(n, 1LL, 100000000LL, "card");
    inf.readEoln();

    inf.readEof();
}
