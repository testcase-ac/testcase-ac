#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 50000000, "N");
    inf.readEoln();

    inf.readInt(1, 100, "A");
    inf.readSpace();
    inf.readInt(1, 3, "D");
    inf.readSpace();
    inf.readInt(1, 1000, "H");
    inf.readEoln();

    inf.readInt(1, 100, "MA");
    inf.readSpace();
    inf.readInt(1, 3, "MD");
    inf.readSpace();
    inf.readInt(1, 1000, "MH");
    inf.readEoln();

    inf.readLong(1LL, 1000000000LL, "Ap");
    inf.readSpace();
    inf.readInt(0, 99, "Aa");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "Dp");
    inf.readSpace();
    inf.readInt(0, 2, "Da");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "Hp");
    inf.readSpace();
    inf.readInt(0, 999, "Ha");
    inf.readEoln();

    inf.readEof();
}
