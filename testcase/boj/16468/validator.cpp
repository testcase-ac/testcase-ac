#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 300, "N");
    inf.readSpace();
    inf.readInt(1, 300, "L");
    inf.readEoln();
    inf.readEof();
}
