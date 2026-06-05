#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100000, "E");
    inf.readSpace();
    inf.readInt(0, 100000, "EM");
    inf.readSpace();
    inf.readInt(0, 100000, "M");
    inf.readSpace();
    inf.readInt(0, 100000, "MH");
    inf.readSpace();
    inf.readInt(0, 100000, "H");
    inf.readEoln();

    inf.readEof();
}
