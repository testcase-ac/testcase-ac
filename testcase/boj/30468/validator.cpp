#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "STR");
    inf.readSpace();
    inf.readInt(1, 100, "DEX");
    inf.readSpace();
    inf.readInt(1, 100, "INT");
    inf.readSpace();
    inf.readInt(1, 100, "LUK");
    inf.readSpace();
    inf.readInt(1, 100, "N");
    inf.readEoln();
    inf.readEof();
}
