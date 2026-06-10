#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 23, "H");
    inf.readSpace();
    inf.readInt(0, 59, "M");
    inf.readSpace();
    inf.readInt(0, 59, "S");
    inf.readEoln();
    inf.readEof();
}
