#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 9, "N");
    inf.readSpace();
    inf.readInt(2, 18, "L");
    inf.readEoln();
    inf.readEof();
}
