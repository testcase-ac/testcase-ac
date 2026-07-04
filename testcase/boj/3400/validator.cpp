#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(2, 38, "n");
    inf.readSpace();
    inf.readInt(1, 19, "d");
    inf.readEoln();
    inf.readEof();
}
