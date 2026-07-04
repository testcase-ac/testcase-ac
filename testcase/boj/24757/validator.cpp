#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "Delta_L");
    inf.readSpace();
    inf.readInt(1, 100, "Delta_W");
    inf.readSpace();
    inf.readInt(1, 100, "G");
    inf.readSpace();
    inf.readInt(0, 99, "L");
    inf.readEoln();
    inf.readEof();
}
