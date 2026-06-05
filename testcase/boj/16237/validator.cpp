#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "A");
    inf.readSpace();
    inf.readInt(0, 1000, "B");
    inf.readSpace();
    inf.readInt(0, 1000, "C");
    inf.readSpace();
    inf.readInt(0, 1000, "D");
    inf.readSpace();
    inf.readInt(0, 1000, "E");
    inf.readEoln();
    inf.readEof();
}
