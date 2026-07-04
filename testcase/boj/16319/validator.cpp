#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 5, "n");
    inf.readSpace();
    int m = inf.readInt(1, 5, "m");
    inf.readSpace();
    inf.readInt(1, 100, "d");
    inf.readEoln();

    inf.readInts(n, 1, 6, "own_health");
    inf.readEoln();

    inf.readInts(m, 1, 6, "opponent_health");
    inf.readEoln();

    inf.readEof();
}
