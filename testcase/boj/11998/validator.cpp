#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "X");
    inf.readSpace();
    inf.readInt(1, 100, "Y");
    inf.readSpace();
    inf.readInt(1, 100, "K");
    inf.readSpace();
    inf.readInt(1, 200, "M");
    inf.readEoln();
    inf.readEof();
}
