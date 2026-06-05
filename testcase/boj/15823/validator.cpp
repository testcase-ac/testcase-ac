#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    inf.readInt(1, n, "m");
    inf.readEoln();

    inf.readInts(n, 1, 500000, "card_id");
    inf.readEoln();
    inf.readEof();
}
