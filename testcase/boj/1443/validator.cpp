#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 8, "D");
    inf.readSpace();
    inf.readInt(0, 30, "P");
    inf.readEoln();
    inf.readEof();
}
