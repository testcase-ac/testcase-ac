#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 999, "w");
    inf.readSpace();
    inf.readInt(1, 999, "h");
    inf.readSpace();
    inf.readInt(1, 99, "d");
    inf.readEoln();
    inf.readEof();
}
