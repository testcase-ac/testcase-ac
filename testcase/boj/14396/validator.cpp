#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 2000, "N");
    inf.readSpace();
    inf.readInt(0, 2000, "M");
    inf.readEoln();
    inf.readEof();
}
