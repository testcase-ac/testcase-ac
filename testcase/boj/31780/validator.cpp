#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100000000, "X");
    inf.readSpace();
    inf.readInt(0, 20, "M");
    inf.readEoln();
    inf.readEof();
}
