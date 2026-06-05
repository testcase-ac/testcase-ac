#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 10000000, "N");
    inf.readEoln();

    inf.readInt(1, 10000, "A");
    inf.readSpace();
    inf.readInt(1, 10000000, "P_A");
    inf.readSpace();
    inf.readInt(1, 10000, "B");
    inf.readSpace();
    inf.readInt(1, 10000000, "P_B");
    inf.readEoln();

    inf.readEof();
}
