#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 20, "n");
    inf.readSpace();
    inf.readInt(1, 1000000000, "t");
    inf.readEoln();

    int card_count = 1 << n;
    inf.readLongs(card_count, 1LL, 1000000000LL, "a_i");
    inf.readEoln();

    inf.readEof();
}
