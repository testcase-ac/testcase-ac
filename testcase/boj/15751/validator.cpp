#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100, "a");
    inf.readSpace();
    inf.readInt(0, 100, "b");
    inf.readSpace();
    inf.readInt(0, 100, "x");
    inf.readSpace();
    inf.readInt(0, 100, "y");
    inf.readEoln();
    inf.readEof();
}
