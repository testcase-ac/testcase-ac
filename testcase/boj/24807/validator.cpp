#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "b");
    inf.readSpace();
    inf.readInt(1, 100, "d");
    inf.readSpace();
    inf.readInt(1, 100, "c");
    inf.readSpace();
    inf.readInt(0, 250, "l");
    inf.readEoln();
    inf.readEof();
}
