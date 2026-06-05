#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000000, "x");
    inf.readSpace();
    inf.readInt(0, 1000000, "y");
    inf.readEoln();

    inf.readEof();
}
