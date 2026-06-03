#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int d1 = inf.readInt(1, 2000, "D_1");
    inf.readSpace();
    int d2 = inf.readInt(d1, 2000, "D_2");
    inf.readEoln();
    inf.readEof();
}
