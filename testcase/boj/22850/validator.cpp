#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000, "N");
    inf.readSpace();
    inf.readInt(1, 100000, "M");
    inf.readEoln();
    inf.readEof();
}
