#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "X");
    inf.readSpace();
    inf.readInt(1, 100, "Y");
    inf.readSpace();
    inf.readInt(1, 100, "P1");
    inf.readSpace();
    inf.readInt(1, 100, "P2");
    inf.readEoln();
    inf.readEof();
}
