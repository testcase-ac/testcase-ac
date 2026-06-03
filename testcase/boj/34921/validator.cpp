#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100, "A");
    inf.readSpace();
    inf.readInt(0, 31, "T");
    inf.readEoln();
    inf.readEof();
}
