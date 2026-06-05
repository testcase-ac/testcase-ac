#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "P");
    inf.readSpace();
    inf.readInt(1, 100, "M");
    inf.readSpace();
    inf.readInt(1, 100, "C");
    inf.readEoln();

    inf.readInt(0, 1000000000, "X");
    inf.readEoln();
    inf.readEof();
}
