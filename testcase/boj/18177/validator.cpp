#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200000, "N");
    inf.readSpace();
    int k = inf.readInt(1, n, "K");
    inf.readEoln();

    inf.readInts(n, 1, (1 << 30) - 1, "schedule");
    inf.readEoln();

    inf.readEof();
}
