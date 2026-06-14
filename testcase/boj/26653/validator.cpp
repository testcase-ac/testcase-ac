#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 20, "N");
    inf.readSpace();
    inf.readInt(1, 1000000000, "M");
    inf.readEoln();
    inf.readEof();
}
