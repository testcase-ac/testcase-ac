#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(10000, 10000, "N");
    inf.readSpace();
    inf.readInt(600000, 600000, "M");
    inf.readEoln();
    inf.readEof();
}
