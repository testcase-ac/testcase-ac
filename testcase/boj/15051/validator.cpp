#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 1000, "A_1");
    inf.readEoln();
    inf.readInt(0, 1000, "A_2");
    inf.readEoln();
    inf.readInt(0, 1000, "A_3");
    inf.readEoln();
    inf.readEof();
}
