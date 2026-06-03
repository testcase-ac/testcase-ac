#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000000, "N");
    inf.readSpace();
    inf.readInt(2, 9, "d");
    inf.readEoln();
    inf.readEof();
}
