#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    constexpr int MAX_VALUE = 500000;

    int n = inf.readInt(1, MAX_VALUE, "N");
    inf.readSpace();
    inf.readInt(1, MAX_VALUE, "k");
    inf.readSpace();
    inf.readInt(1, MAX_VALUE, "d");
    inf.readEoln();

    inf.readInts(n, 1, MAX_VALUE, "S_i");
    inf.readEoln();

    inf.readEof();
}
