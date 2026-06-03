#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 2000, "N");
    inf.readSpace();
    inf.readInt(1, 2000, "L");
    inf.readEoln();
    inf.readEof();
}
