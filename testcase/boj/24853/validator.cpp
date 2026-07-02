#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100, "X");
    inf.readSpace();
    inf.readInt(1, 100000, "T");
    inf.readEoln();
    inf.readEof();
}
