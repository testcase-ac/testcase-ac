#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 738, "S_ab");
    inf.readEoln();

    inf.readInt(1, 738, "M_a");
    inf.readSpace();
    inf.readInt(1, 738, "F_ab");
    inf.readSpace();
    inf.readInt(1, 738, "M_b");
    inf.readEoln();

    inf.readEof();
}
