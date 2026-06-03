#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, 1000, "M");
    inf.readSpace();
    inf.readInt(0, 1000000000, "K");
    inf.readEoln();
    inf.readEof();
}
