#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 50, "D");
    inf.readSpace();
    inf.readInt(1, 50, "R");
    inf.readEoln();
    inf.readEof();
}
