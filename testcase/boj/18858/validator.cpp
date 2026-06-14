#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "N");
    inf.readSpace();
    inf.readInt(1, 100, "M");
    inf.readEoln();
    inf.readEof();
}
