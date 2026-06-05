#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 359, "n_1");
    inf.readEoln();
    inf.readInt(0, 359, "n_2");
    inf.readEoln();
    inf.readEof();
}
