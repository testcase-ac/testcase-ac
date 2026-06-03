#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 2048, "S");
    inf.readSpace();
    inf.readInt(1, 1023, "M");
    inf.readEoln();
    inf.readEof();
}
