#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 1000, "n");
    inf.readSpace();
    inf.readInt(2, 1000, "m");
    inf.readEoln();
    inf.readEof();
}
