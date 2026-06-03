#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "X");
    inf.readEoln();
    inf.readInt(1, 100, "Y");
    inf.readEoln();
    inf.readInt(1, 100, "Z");
    inf.readEoln();
    inf.readEof();
}
