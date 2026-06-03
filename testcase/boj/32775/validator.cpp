#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 738, "S_ab");
    inf.readEoln();
    inf.readInt(1, 738, "F_ab");
    inf.readEoln();
    inf.readEof();
}
