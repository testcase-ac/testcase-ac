#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "x");
    inf.readSpace();
    inf.readInt(1, 1000, "y");
    inf.readEoln();
    inf.readEof();
}
