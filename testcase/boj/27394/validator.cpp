#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000000, "t");
    inf.readSpace();
    inf.readInt(0, 1000000, "s");
    inf.readEoln();
    inf.readEof();
}
