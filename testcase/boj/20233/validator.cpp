#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(0, 100, "a");
    inf.readEoln();
    inf.readInt(0, 100, "x");
    inf.readEoln();
    inf.readInt(0, 100, "b");
    inf.readEoln();
    inf.readInt(0, 100, "y");
    inf.readEoln();
    inf.readInt(1, 1440, "T");
    inf.readEoln();
    inf.readEof();
}
