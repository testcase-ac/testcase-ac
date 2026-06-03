#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 10000, "p_ab");
    inf.readSpace();
    inf.readInt(1, 10000, "p_bc");
    inf.readSpace();
    inf.readInt(1, 10000, "p_cd");
    inf.readEoln();
    inf.readEof();
}
