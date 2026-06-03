#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 99999, "N");
    inf.readSpace();
    inf.readInt(1, 99999, "T");
    inf.readSpace();
    inf.readInt(0, 99999, "G");
    inf.readEoln();
    inf.readEof();
}
