#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(23, 9999, "N");
    inf.readSpace();
    inf.readInt(1, 9, "s");
    inf.readSpace();
    inf.readInt(1, 12, "M");
    inf.readEoln();
    inf.readEof();
}
