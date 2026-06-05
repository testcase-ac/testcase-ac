#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 1000, "r_1");
    inf.readSpace();
    inf.readInt(1, 1000, "r_2");
    inf.readSpace();
    inf.readInt(1, 1000, "r_3");
    inf.readEoln();
    inf.readEof();
}
