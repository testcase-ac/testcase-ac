#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000000, "d_1");
    inf.readSpace();
    inf.readInt(1, 1000000, "d_2");
    inf.readSpace();
    inf.readInt(1, 1000000, "d_3");
    inf.readEoln();
    inf.readEof();
}
