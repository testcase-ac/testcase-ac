#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 77777, "N");
    inf.readSpace();
    inf.readInt(1, 77777, "M");
    inf.readEoln();
    inf.readEof();
}
