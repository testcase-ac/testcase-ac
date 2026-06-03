#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "A");
    inf.readSpace();
    inf.readInt(0, 1000, "P");
    inf.readEoln();
    inf.readEof();
}
