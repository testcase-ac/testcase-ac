#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 200, "n");
    inf.readSpace();
    inf.readInt(2, 200, "m");
    inf.readEoln();
    inf.readEof();
}
