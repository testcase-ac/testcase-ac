#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int maxValue = (1 << 30) - 1;

    int n = inf.readInt(1, 200000, "n");
    inf.readSpace();
    inf.readInt(1, maxValue, "k");
    inf.readEoln();

    inf.readInts(n, 1, maxValue, "a_i");
    inf.readEoln();

    inf.readEof();
}
