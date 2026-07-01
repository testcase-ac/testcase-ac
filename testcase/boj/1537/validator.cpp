#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "X");
    inf.readSpace();
    inf.readInt(1, 2000000000, "G");
    inf.readEoln();
    inf.readEof();
}
