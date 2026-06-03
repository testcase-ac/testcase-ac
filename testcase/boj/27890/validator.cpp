#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "x0");
    inf.readSpace();
    inf.readInt(0, 1000, "N");
    inf.readEoln();
    inf.readEof();
}
